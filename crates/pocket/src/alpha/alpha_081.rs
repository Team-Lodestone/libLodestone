use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::util::McVersion;
use lodestone_level::block::conversion::{get_internal_block_id, get_version_block_id};
use lodestone_level::block::BlockId;
use lodestone_level::level::chunk::{Chunk, Light, CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::region::ChunkLocation;
use lodestone_level::level::{Coords, Level};
use rayon::iter::{IntoParallelRefMutIterator, ParallelIterator, IndexedParallelIterator};
use rayon::prelude::IntoParallelRefIterator;
use std::io::{Cursor, Read, Seek, SeekFrom, Write};

const MCPE_ALPHA_LEVEL_CHUNK_HEIGHT: u16 = 128;

pub trait Alpha081Level {
    fn read_alpha081_chunks_dat(version: McVersion, data: Vec<u8>) -> Result<Level, String>;
    fn read_alpha081_chunks_dat_into_existing(&mut self, version: McVersion, data: Vec<u8>);
    fn write_alpha081_chunks_dat(&mut self, version: McVersion) -> Vec<u8>;
}

pub trait Alpha081Chunk {
    fn read_alpha081(version: McVersion, data: &[u8]) -> Result<Chunk, String>;
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8>;
}

impl Alpha081Level for Level {
    fn read_alpha081_chunks_dat(version: McVersion, data: Vec<u8>) -> Result<Level, String>{
        let mut lvl = Level::new();
        lvl.read_alpha081_chunks_dat_into_existing(version, data);
        Ok(lvl)
    }
    fn read_alpha081_chunks_dat_into_existing(&mut self, version: McVersion, data: Vec<u8>) {
        let mut c = Cursor::new(data);
        let mut locations = vec![(ChunkLocation::default(), Coords::default()); 1024];

        // Parallel enumerator?
        for l in locations.iter_mut().enumerate() {
            let size = c.read_u8().expect("Size in location");
            let offset = c.read_u24::<LittleEndian>().expect("Offset in location");

            if size == 0 {
                continue;
            }

            if size != 0x15 {
                continue; /* TODO: ERROR somehow? */
            }

            *l.1 = (ChunkLocation { offset, size }, Coords {x: (l.0 % 32) as i32, z: (l.0 / 32) as i32} );
        }

        let chunks: Vec<(Coords, Chunk)> = locations
            .par_iter()
            .filter_map(|l| {
                if l.0.size == 0 {
                    return None;
                }
                let mut c = c.clone();
                c.set_position((l.0.offset as u64) * 0x1000 + 4);
                
                // Third-party tools (some PocketMine converter?) don't seem to write the minimum bytes required. Minecraft appears to ignore this, and directaxe does so too.
                // So allocate the minimum needed by the data
                let mut chunk_data: Vec<u8> = vec![0; 82180 - 4];
                c.read_exact(&mut chunk_data).expect("Failed to read chunk data");

                let ch = Chunk::read_alpha081(version, &chunk_data).expect("Failed to read chunk");
                Some((l.1.clone(), ch))
            })
            .collect();


        for (coords, chunk) in chunks {
            self.add_chunk(coords, chunk);
        }
    }
    fn write_alpha081_chunks_dat(&mut self, version: McVersion) -> Vec<u8> {
        let out: Vec<u8> = Vec::with_capacity(32* 32 * 4 + (0x1000 * 0x15 * self.get_chunk_count()));
        let mut c = Cursor::new(out);
        // TODO: Region file says it will need a chunk writing limit, when that's done implement it here
        for (num, (coords, chunk)) in self.get_chunks_mut().iter_mut().enumerate() {
            /* TODO: Complain and somehow clamp coordinates if they're not in range? */
            c.set_position((coords.x + coords.z * 32) as u64* 4);
            c.write_u8(0x15).expect("Failed to write chunk size");
            c.write_u24::<LittleEndian>(num as u32 * 0x15 + 1).expect("Failed to write chunk offset");
            c.set_position((num as u64 * 0x15 + 1) * 0x1000);

            let mut ch = chunk.write_alpha081(version);
            c.write_all(ch.as_mut_slice()).expect("Failed to write chunk data");

        }
        c.into_inner()
    }
}


const MCPE_CHUNKS_DAT_DATA_OFFSET: usize = CHUNK_WIDTH as usize * CHUNK_LENGTH as usize * MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize;
const MCPE_CHUNKS_DAT_SKYLIGHT_OFFSET: usize = MCPE_CHUNKS_DAT_DATA_OFFSET + MCPE_CHUNKS_DAT_DATA_OFFSET / 2;
const MCPE_CHUNKS_DAT_BLOCKLIGHT_OFFSET: usize = MCPE_CHUNKS_DAT_SKYLIGHT_OFFSET + MCPE_CHUNKS_DAT_DATA_OFFSET / 2;
//const MCPE_CHUNKS_DAT_BIOME_OFFSET: usize = MCPE_CHUNKS_DAT_BLOCKLIGHT_OFFSET + MCPE_CHUNKS_DAT_DATA_OFFSET / 2;

impl Alpha081Chunk for Chunk {
    fn read_alpha081(version: McVersion, data: &[u8]) -> Result<Chunk, String> {

        let mut c = Chunk::new(MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as i16);

        for x in 0..CHUNK_WIDTH as u16 {
            for z in 0..CHUNK_LENGTH as u16 {
                for y in 0..MCPE_ALPHA_LEVEL_CHUNK_HEIGHT {
                    let flat_index = z as usize + x as usize * CHUNK_LENGTH as usize;
                    let block_index = y as usize + flat_index * MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize;
                    let meta_index  = MCPE_CHUNKS_DAT_DATA_OFFSET + block_index / 2;
                    let skylight_index  = MCPE_CHUNKS_DAT_SKYLIGHT_OFFSET + block_index / 2;
                    let blocklight_index  = MCPE_CHUNKS_DAT_BLOCKLIGHT_OFFSET + block_index / 2;
                    //let biome_index = MCPE_CHUNKS_DAT_BIOME_OFFSET + flat_index;

                    let half_index = block_index % 2;

                    let block_id = data[block_index];
                    let block_meta = (data[meta_index] >> (4 * half_index)) & 0x0f;
                    let block_skylight = (data[skylight_index] >> (4 * half_index)) & 0x0f;
                    let block_blocklight = (data[blocklight_index] >> (4 * half_index)) & 0x0f;
                    // TODO: Biome data when dexrn adds it.
                    if block_id != 0 {
                        c.get_or_create_chunk_section_mut(y as i16);
                        
                        let blk = get_internal_block_id(version, &BlockId::NumericWithData(block_id as u16, block_meta as u16));
                        match blk {
                            Some(blk) => {
                                c.set_block(x as i8, y as i16, z as i8, blk);
                            }
                            None => {}
                        }
                    }
                    c.set_light(Light::SKY, x as i8, y as i16, z as i8, block_skylight);
                    c.set_light(Light::BLOCK, x as i8, y as i16, z as i8, block_blocklight);
                }
            }
                }

        Ok(c)
    }
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8> {
        let out: Vec<u8> = Vec::new();
        let mut c = Cursor::new(out);


        let mut blocks = vec![vec![vec![0 as u8; MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize]; CHUNK_LENGTH as usize]; CHUNK_WIDTH as usize];
        let mut meta = vec![vec![vec![0 as u8; MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize / 2]; CHUNK_LENGTH as usize]; CHUNK_WIDTH as usize];
        let mut skylight = vec![vec![vec![0 as u8; MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize / 2]; CHUNK_LENGTH as usize]; CHUNK_WIDTH as usize];
        let mut blocklight = vec![vec![vec![0 as u8; MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize / 2]; CHUNK_LENGTH as usize]; CHUNK_WIDTH as usize];
        let mut biome = vec![vec![0 as u8; CHUNK_LENGTH as usize]; CHUNK_WIDTH as usize];
        for x in 0..CHUNK_WIDTH as i8 {
            for z in 0..CHUNK_LENGTH as i8 {
                for y in 0..MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as i16 {
                    let byte_index = y % 2 * 4;
                    let blk_internal = self.get_block(x, y, z);
                    let blk = get_version_block_id(version, &blk_internal);
                    blocks[x as usize][z as usize][y as usize] = usize::try_from(blk).unwrap_or(0) as u8;
                    // TODO: Meta
                    skylight[x as usize][z as usize][y as usize /2] |= self.get_light(Light::SKY, x, y, z) << byte_index;
                    blocklight[x as usize][z as usize][y as usize /2] |= self.get_light(Light::BLOCK, x, y, z) << byte_index;
                }
            }
        }

        c.write_all(&blocks.into_iter().flatten().flatten().collect::<Vec::<u8>>().as_slice()).expect("Failed to write blocks");
        c.write_all(&meta.into_iter().flatten().flatten().collect::<Vec::<u8>>().as_slice()).expect("Failed to write meta");
        c.write_all(&skylight.into_iter().flatten().flatten().collect::<Vec::<u8>>().as_slice()).expect("Failed to write skylight");
        c.write_all(&blocklight.into_iter().flatten().flatten().collect::<Vec::<u8>>().as_slice()).expect("Failed to write blocklight");
        c.write_all(&biome.into_iter().flatten().collect::<Vec<u8>>().as_slice()).expect("Failed to write biome data");

        c.into_inner()
    }
}