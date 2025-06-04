mod version;

use byteorder::{BigEndian, ReadBytesExt};
use flate2::read::{GzDecoder, ZlibDecoder};
use lodestone_common::level::region::{ChunkLocation, Compression};
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::{Chunk, CHUNK_LENGTH};
use lodestone_level::level::{metadata, Coords, Level};
use quartz_nbt::io::Flavor;
use quartz_nbt::{io, NbtCompound, NbtList, NbtTag};
use std::io::{Cursor, Read};

pub trait Anvil {
    fn read_anvil(data: Vec<u8>) -> Result<Level, String>;
    fn read_anvil_into_existing(&mut self, data: Vec<u8>) -> Result<(), String>;
    // fn write_anvil(&mut self, out: &mut Vec<u8>);
}
pub trait AnvilChunk {
    fn read_anvil(data: Vec<u8>) -> Result<(Chunk, i32, i32), String>;
    // fn write_anvil(&self, out: &mut Vec<u8>, x: i32, z: i32);
}

impl Anvil for Level {
    fn read_anvil(data: Vec<u8>) -> Result<Level, String> {
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

        // TODO: find a way to make parallel
        for l in locations.iter() {
            if (l.size as usize) * 4096 == 0 {
                continue;
            }

            c.set_position((l.offset as u64) * 4096);

            let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
            let comp = c.read_i8().expect("Chunk compression");
            let compression = Compression::try_from(comp).expect("Chunk compression enum");

            let mut compressed = vec![0u8; (len - 1) as usize];
            // wtf is this slice stuff
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

            let ch = Chunk::read_anvil(chunk_data).expect("Region Chunk from data");
            level.add_chunk(Coords { x: ch.1, z: ch.2 }, ch.0);
        }

        Ok(level)
    }

    fn read_anvil_into_existing(&mut self, data: Vec<u8>) -> Result<(), String> {
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

        for l in locations.iter() {
            if (l.size as usize) * 4096 == 0 {
                continue;
            }

            c.set_position((l.offset as u64) * 4096);

            let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
            let comp = c.read_i8().expect("Chunk compression");
            let compression = Compression::try_from(comp).expect("Chunk compression enum");

            let mut compressed = vec![0u8; (len - 1) as usize];
            // wtf is this slice stuff
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

            let ch = Chunk::read_anvil(chunk_data).expect("Anvil Chunk from data");
            self.add_chunk(Coords { x: ch.1, z: ch.2 }, ch.0);
        }
        Ok(())
    }
}

impl AnvilChunk for Chunk {
    fn read_anvil(data: Vec<u8>) -> Result<(Chunk, i32, i32), String> {
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::Uncompressed)
            .expect("Chunk NBT data")
            .0;

        let version: i32 = nbt.get("DataVersion").unwrap_or(0);

        // I created 24 instances to find the correct version (17w47a)
        // and then on the wiki talk page, someone had already mentioned it, back in 2017...
        // Why didn't the search page show me the message???
        if version >= 1451 {
            panic!("Section palettes (introduced in 17w47a) are not yet supported.");
        }

        // TODO: we do not handle extended block IDs yet.

        let level: &NbtCompound = nbt.get("Level").expect("Level compound tag");

        let x: i32 = level.get("xPos").expect("Chunk x position");
        let z: i32 = level.get("zPos").expect("Chunk z position");
        let last_update: i64 = level.get("LastUpdate").expect("Chunk last modified");
        let inhabited_time: i64 = level.get("InhabitedTime").expect("Chunk inhabited time");
        // let entities: &NbtList = level.get("Entities").expect("Chunk entities");
        // let tile_entities: &NbtList = level.get("TileEntities").expect("Chunk tile entities");
        let has_populated: i8 = level.get("TerrainPopulated").expect("Chunk has populated"); // DOES NOT EXIST ON 1.16 (TODO: DataVersion check to see what is available)
        let has_light_populated: i8 = level
            .get("LightPopulated")
            .expect("Chunk light has populated");

        let mut c = Chunk::new(256);

        c.custom_data
            .set_value(metadata::LAST_UPDATE.to_string(), last_update);
        c.custom_data
            .set_value(metadata::INHABITED_TIME.to_string(), inhabited_time);
        c.custom_data
            .set_value(metadata::TERRAIN_POPULATED.to_string(), has_populated);
        c.custom_data
            .set_value(metadata::LIGHT_POPULATED.to_string(), has_light_populated);

        // love sections
        let sections: &NbtList = level.get("Sections").expect("Chunk sections");

        sections.iter().for_each(|s| {
            if let NbtTag::Compound(section) = s {
                let sy: i8 = section.get("Y").expect("Section Y");
                let blocks: &[u8] = section.get("Blocks").expect("Section blocks");

                for y in 0..16 {
                    for z in 0..16 {
                        for x in 0..16 {
                            let i = y * 16 * 16 + z * 16 + x;

                            c.blocks[(sy as usize * 16 + y)
                                + z * c.height as usize
                                + x * c.height as usize * CHUNK_LENGTH as usize] = blocks[i] as u16;
                        }
                    }
                }
            }
        });

        Ok((c, x, z))
    }
}
