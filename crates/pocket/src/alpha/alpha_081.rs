use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::util::McVersion;
use lodestone_level::block::conversion::get_internal_block_id;
use lodestone_level::block::BlockId;
use lodestone_level::level::chunk::{Chunk, Light, CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::metadata::BLOCK_LIGHT;
use lodestone_level::level::region::ChunkLocation;
use lodestone_level::level::{Coords, Level};
use rayon::iter::ParallelIterator;
use rayon::prelude::IntoParallelRefIterator;
use std::io::{Cursor, Read, Seek, SeekFrom, Write};

const MCPE_ALPHA_LEVEL_CHUNK_HEIGHT: u16 = 128;

pub trait Alpha081Level {
    fn read_alpha081(version: McVersion, data: Vec<u8>) -> Result<Level, String>;
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8>;
}

pub trait Alpha081Chunk {
    fn read_alpha081(version: McVersion, data: &[u8]) -> Result<Chunk, String>;
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8>;
}

impl Alpha081Level for Level {
    fn read_alpha081(version: McVersion, data: Vec<u8>) -> Result<Level, String> {
        let mut c = Cursor::new(data);
        let mut locations = vec![(ChunkLocation::default(), Coords::default()); 1024];
        let mut level = Level::new();

        for l in locations.iter_mut().enumerate() {
            let size = c.read_u8().expect("Size in location");
            let offset = c.read_u24::<LittleEndian>().expect("Offset in location");
            
            if size != 0x15 {
                /* TODO: Error recovery not possible with panics? */
                return Err("Unsupported chunk size specified in index!".to_string());
            }

            *l.1 = (ChunkLocation { offset, size }, Coords {x: (l.0 % 32) as i32, z: (l.0 / 32) as i32} );
        }

        let chunks: Vec<(&Coords, Chunk)> = locations
            .par_iter()
            .filter_map(|l| {
                if l.0.size == 0 {
                    return None;
                }
                let mut c = c.clone();
                c.set_position((l.0.offset as u64) * 0x1000 + 4);
                let chunk_size = c.read_u32::<LittleEndian>().expect("Can't read chunk length in chunk structure");
                if chunk_size != 82180 {
                    panic!("Unsupported chunk size specified in chunk structure");
                }

                let mut chunk_data: Vec<u8> = vec![0; chunk_size as usize];
                c.read_exact(&mut chunk_data).expect("Failed to read chunk data");

                let ch = Chunk::read_alpha081(version, &chunk_data).expect("Failed to read chunk");
                Some((&l.1, ch))
            })
            .collect();

        Ok(level)
    }
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8> {
        Vec::new()
    }
}


const MCPE_CHUNKS_DAT_DATA_OFFSET: usize = CHUNK_WIDTH as usize * CHUNK_LENGTH as usize * MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as usize;
const MCPE_CHUNKS_DAT_SKYLIGHT_OFFSET: usize = MCPE_CHUNKS_DAT_DATA_OFFSET + MCPE_CHUNKS_DAT_DATA_OFFSET / 2;
const MCPE_CHUNKS_DAT_BLOCKLIGHT_OFFSET: usize = MCPE_CHUNKS_DAT_SKYLIGHT_OFFSET + MCPE_CHUNKS_DAT_DATA_OFFSET / 2;
//const MCPE_CHUNKS_DAT_BIOME_OFFSET: usize = MCPE_CHUNKS_DAT_BLOCKLIGHT_OFFSET + MCPE_CHUNKS_DAT_DATA_OFFSET / 2;

impl Alpha081Chunk for Chunk {
    fn read_alpha081(version: McVersion, data: &[u8]) -> Result<Chunk, String> {

        let mut c = Chunk::new(MCPE_ALPHA_LEVEL_CHUNK_HEIGHT as i16);

        for y in 0..MCPE_ALPHA_LEVEL_CHUNK_HEIGHT {
            for z in 0..CHUNK_LENGTH as u16 {
                for x in 0..CHUNK_WIDTH as u16 {
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
        Vec::new()
    }
}