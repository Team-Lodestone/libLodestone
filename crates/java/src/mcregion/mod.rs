use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use flate2::read::{GzDecoder, ZlibDecoder};
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_common::util::McVersion;
use lodestone_level::block::conversion::get_internal_block_id;
use lodestone_level::block::BlockId;
use lodestone_level::level::chunk::Chunk;
use lodestone_level::level::region::ChunkLocation;
use lodestone_level::level::region::Compression;
use lodestone_level::level::{metadata, Coords, Level};
use quartz_nbt::io::Flavor;
use quartz_nbt::{io, NbtCompound, NbtList};
use rayon::iter::ParallelIterator;
use rayon::prelude::IntoParallelRefIterator;
use std::io::{Cursor, Read, Seek, SeekFrom, Write};

/// TODO: we need to make write_mcr use coords
/// also need to read/write region directories.
/// but entire world dir should be it's own impl in different module.

pub trait Region {
    /// Creates a new Level from an MCR file
    fn read_mcr(version: McVersion, data: Vec<u8>) -> Result<Level, String>;
    /// Reads an MCR level into an existing Level
    fn read_mcr_into_existing(&mut self, version: McVersion, data: Vec<u8>);
    /// Writes out the MCR file
    fn write_mcr(&mut self, version: McVersion) -> Vec<u8>;
}
pub trait MCRChunk {
    fn read_mcr(version: McVersion, data: Vec<u8>) -> Result<(Chunk, Coords), String>;
    fn write_mcr(&self, version: McVersion, coords: &Coords) -> Vec<u8>;
}

impl Region for Level {
    fn read_mcr(version: McVersion, data: Vec<u8>) -> Result<Level, String> {
        let mut c = Cursor::new(data);
        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];
        let mut level = Level::new();

        for l in locations.iter_mut() {
            let offset = c.read_u24::<BigEndian>().expect("Offset in location");
            let size = c.read_u8().expect("Size in location");

            *l = ChunkLocation { offset, size };
        }

        for ts in timestamps.iter_mut() {
            *ts = c.read_i32::<BigEndian>().expect("Chunk timestamp");
        }

        let chunks: Vec<(Coords, Chunk)> = locations
            .par_iter()
            .filter_map(|l| {
                if l.size == 0 {
                    return None;
                }

                let mut c = c.clone();
                c.set_position((l.offset as u64) * 4096);

                let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
                let comp = c.read_i8().expect("Chunk compression");
                let compression = Compression::try_from(comp).expect("Chunk compression enum");

                let mut compressed = vec![0u8; (len - 1) as usize];
                c.read_exact(compressed.as_mut_slice())
                    .expect("Compressed chunk data");

                let mut chunk_data: Vec<u8> = Vec::new();

                // TODO: support the other 2 methods
                let dec: Option<Box<dyn Read>> = match compression {
                    Compression::Zlib => {
                        Some(Box::new(ZlibDecoder::new(Cursor::new(compressed.clone()))))
                    } // cloning seems really janky...?
                    Compression::GZip => {
                        Some(Box::new(GzDecoder::new(Cursor::new(compressed.clone()))))
                    }
                    Compression::None => None,
                    _ => {
                        panic!("Unsupported compression format!")
                    } // is this a good idea? I don't know if you can "catch" a panic...
                };

                if compression != Compression::None {
                    dec.expect("Decompressor")
                        .read_to_end(&mut chunk_data)
                        .expect("Decompressed chunk data");
                } else {
                    chunk_data = compressed.to_vec();
                }

                let ch = Chunk::read_mcr(version, chunk_data).expect("Region Chunk from data");
                Some((ch.1, ch.0))
            })
            .collect();

        for (coords, chunk) in chunks {
            level.add_chunk(coords, chunk);
        }

        Ok(level)
    }

    fn read_mcr_into_existing(&mut self, version: McVersion, data: Vec<u8>) {
        let mut c = Cursor::new(data);
        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];

        for l in locations.iter_mut() {
            let offset = c.read_u24::<BigEndian>().expect("Offset in location");
            let size = c.read_u8().expect("Size in location");

            *l = ChunkLocation { offset, size };
        }

        for ts in timestamps.iter_mut() {
            *ts = c.read_i32::<BigEndian>().expect("Chunk timestamp");
        }

        let chunks: Vec<(Coords, Chunk)> = locations
            .par_iter()
            .filter_map(|l| {
                if l.size == 0 {
                    return None;
                }

                let mut c = c.clone();
                c.set_position((l.offset as u64) * 4096);

                let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
                let comp = c.read_i8().expect("Chunk compression");
                let compression = Compression::try_from(comp).expect("Chunk compression enum");

                let mut compressed = vec![0u8; (len - 1) as usize];
                c.read_exact(compressed.as_mut_slice())
                    .expect("Compressed chunk data");

                let mut chunk_data: Vec<u8> = Vec::new();

                // TODO: support the other 2 methods
                let dec: Option<Box<dyn Read>> = match compression {
                    Compression::Zlib => {
                        Some(Box::new(ZlibDecoder::new(Cursor::new(compressed.clone()))))
                    } // cloning seems really janky...?
                    Compression::GZip => {
                        Some(Box::new(GzDecoder::new(Cursor::new(compressed.clone()))))
                    }
                    Compression::None => None,
                    _ => {
                        panic!("Unsupported compression format!")
                    } // is this a good idea? I don't know if you can "catch" a panic...
                };

                if compression != Compression::None {
                    dec.expect("Decompressor")
                        .read_to_end(&mut chunk_data)
                        .expect("Decompressed chunk data");
                } else {
                    chunk_data = compressed.to_vec();
                }

                let ch = Chunk::read_mcr(version, chunk_data).expect("Region Chunk from data");
                Some((ch.1, ch.0))
            })
            .collect();
        for (coords, chunk) in chunks {
            self.add_chunk(coords, chunk);
        }
    }

    // TODO: coordinates
    fn write_mcr(&mut self, version: McVersion) -> Vec<u8> {
        let out: Vec<u8> = Vec::with_capacity(0x2000 + (1000 * self.get_chunk_count()));
        let mut c = Cursor::new(out);

        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];

        c.seek(SeekFrom::Start(0x2000)).expect("Chunk position");

        // TODO: when writing we need to make sure that we're only writing max 1024 chunks
        // meaning we need region coordinate system (separate from Level but in a common impl...)
        for (coords, chunk) in self.get_chunks_mut().iter_mut() {
            chunk.set_height(128);
            let mut ch = chunk.write_mcr(version, coords);

            let len = ch.len();
            let sector_size = ((len + 5) + 4095) / 4096;

            let size = sector_size;
            let offset = c.stream_position().unwrap() / 4096;

            let idx = (coords.x as usize & 31) + ((coords.z as usize & 31) * 32);
            locations[idx] = ChunkLocation {
                offset: offset as u32,
                size: size as u8,
            };
            timestamps[idx] = 0;

            c.write_i32::<BigEndian>(len as i32).expect("Chunk size");
            c.write_i8(2).expect("Chunk compression type");
            c.write_all(ch.as_mut_slice()).expect("Chunk data");

            let p = sector_size * 4096 - (len + 5);
            if p > 0 {
                c.write_all(&vec![0u8; p]).unwrap();
            }
        }

        c.seek(SeekFrom::Start(0)).unwrap();

        for l in locations.iter() {
            c.write_u24::<BigEndian>(l.offset).expect("Offset");
            c.write_u8(l.size).expect("Size");
        }

        c.seek(SeekFrom::Start(0x1000)).unwrap();

        for t in timestamps.iter() {
            c.write_i32::<BigEndian>(*t).expect("Timestamp");
        }

        c.into_inner()
    }
}

impl MCRChunk for Chunk {
    // INCOMPLETE: we need to store the light data correctly
    // plus need entities and all
    fn read_mcr(version: McVersion, data: Vec<u8>) -> Result<(Chunk, Coords), String> {
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::Uncompressed)
            .expect("Chunk NBT data")
            .0;

        let level: &NbtCompound = nbt.get("Level").expect("Level compound tag");

        let x: i32 = level.get("xPos").expect("Chunk x position");
        let z: i32 = level.get("zPos").expect("Chunk z position");
        let last_update: i64 = level.get("LastUpdate").expect("Chunk last modified");
        let blocks: &[u8] = level.get("Blocks").expect("Chunk blocks");
        // let block_data: &[u8] = level.get("Data").expect("Chunk block data");
        // let sky_light: &[u8] = level.get("SkyLight").expect("Chunk sky light");
        // let block_light: &[u8] = level.get("BlockLight").expect("Chunk block light");
        // let height_map: &[u8] = level.get("HeightMap").expect("Chunk heightmap");
        // let entities: &NbtList = level.get("Entities").expect("Chunk entities");
        // let tile_entities: &NbtList = level.get("TileEntities").expect("Chunk tile entities");
        let has_populated: i8 = level.get("TerrainPopulated").expect("Chunk has populated");

        let mut c = Chunk::new(128);

        c.custom_data
            .set_value(metadata::LAST_UPDATE.to_string(), last_update);
        c.custom_data
            .set_value(metadata::TERRAIN_POPULATED.to_string(), has_populated);

        for y in 0..128 {
            for z in 0..16 {
                for x in 0..16 {
                    let i = y + (z * 128 + (x * 128 * 16));

                    let block_id = blocks[i] as u16;
                    if block_id != 0 {
                        c.get_or_create_chunk_section_mut(y as i16);

                        let blk = get_internal_block_id(version, &BlockId::Numeric(block_id));
                        match blk {
                            Some(blk) => {
                                c.set_block(x as i8, y as i16, z as i8, blk);
                            }
                            None => {}
                        }
                    }
                }
            }
        }

        // c.blocks = blocks.to_vec().iter().map(|&x| x as u16).collect();
        // c.data = block_data.to_vec();
        // c.sky_light = sky_light.to_vec();
        // c.block_light = block_light.to_vec();
        // c.height_map = height_map.to_vec();

        Ok((c, Coords { x, z }))
    }

    fn write_mcr(&self, version: McVersion, coords: &Coords) -> Vec<u8> {
        let mut out: Vec<u8> = Vec::new();

        let mut nbt = NbtCompound::new();
        let mut c = NbtCompound::new();

        c.insert("xPos".to_string(), coords.x);
        c.insert("zPos".to_string(), coords.z);
        c.insert(
            "Blocks".to_string(),
            self.get_all_blocks_converted(version)
                .clone()
                .iter()
                .map(|x| usize::try_from(x.clone()).unwrap_or(0) as u8)
                .collect::<Vec<u8>>(),
        );
        // c.insert(
        //     "Data".to_string(),
        //     lodestone_common::io::into_nibble_array(self.get_all_data()),
        // );
        c.insert("Data", vec![0u8; 16384]);
        c.insert("SkyLight".to_string(), vec![0u8; 16384]);
        c.insert("BlockLight".to_string(), vec![0u8; 16384]);
        c.insert(
            "HeightMap".to_string(),
            self.get_heightmap()
                .iter()
                .map(|&x| x as u8)
                .collect::<Vec<u8>>(),
        );
        c.insert("LastUpdate".to_string(), 0i64);
        c.insert("Entities".to_string(), NbtList::new());
        c.insert("TileEntities".to_string(), NbtList::new());
        c.insert("TerrainPopulated".to_string(), 1i8);

        nbt.insert("Level".to_string(), c);

        io::write_nbt(&mut out, Some(""), &nbt, Flavor::ZlibCompressed).unwrap();

        out
    }
}
