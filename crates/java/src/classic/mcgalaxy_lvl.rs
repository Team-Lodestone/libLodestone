use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_common::util::McVersion;
use lodestone_level::block::conversion::get_internal_block_id;
use lodestone_level::block::BlockId;
use lodestone_level::level::chunk::{CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::{metadata, Level};
use rayon::iter::IndexedParallelIterator;
use rayon::iter::ParallelIterator;
use rayon::prelude::IntoParallelRefMutIterator;
use std::io::{Cursor, Read, Write};

pub trait MCGLevel {
    fn read_mcgalaxy_level(version: McVersion, data: Vec<u8>) -> Result<Level, String>;
    fn get_mcgalaxy_level_file_size(&self) -> usize;
    fn write_mcgalaxy_level(&self, version: McVersion) -> Vec<u8>;
}

impl MCGLevel for Level {
    fn read_mcgalaxy_level(version: McVersion, data: Vec<u8>) -> Result<Level, String> {
        let mut c = Cursor::new(data);
        let signature = c.read_u16::<LittleEndian>().unwrap();
        let width = c.read_i16::<LittleEndian>().unwrap();
        let length = c.read_i16::<LittleEndian>().unwrap();
        let height = c.read_i16::<LittleEndian>().unwrap();
        let spawn_x = c.read_i16::<LittleEndian>().unwrap();
        let spawn_z = c.read_i16::<LittleEndian>().unwrap();
        let spawn_y = c.read_i16::<LittleEndian>().unwrap();
        let spawn_yaw = c.read_u8().unwrap();
        let spawn_pitch = c.read_u8().unwrap();

        let mut mcg = Level::new();
        mcg.set_spawn_point(spawn_x as i32, spawn_y as i32, spawn_z as i32);
        mcg.custom_data
            .set_value::<u8>(metadata::SPAWN_YAW.to_string(), spawn_yaw);
        mcg.custom_data
            .set_value::<u8>(metadata::SPAWN_PITCH.to_string(), spawn_pitch);

        println!("sig: {}", signature);
        // note: not required to be 1874 apparently.
        // although why wouldn't it be?
        if signature != 1874 {
            return Err("Signature does not match required '1874'".to_string());
        }

        let min_access_perm = c.read_u8().unwrap();
        let min_build_perm = c.read_u8().unwrap();
        mcg.custom_data
            .set_value::<u8>(metadata::MIN_ACCESS_PERM.to_string(), min_access_perm);
        mcg.custom_data
            .set_value::<u8>(metadata::MIN_BUILD_PERM.to_string(), min_build_perm);

        println!("w: {}, h: {}, l: {}", width, height, length);
        println!("spX: {}, spY: {}, spZ: {}", spawn_x, spawn_y, spawn_z);

        let mut blocks: Vec<u8> = vec![0; (width as usize) * (length as usize) * (height as usize)];

        c.read_exact(&mut blocks)
            .expect("Failed to read block array");

        mcg.create_finite(width as i32, height, length as i32);

        log::debug!("Read into chunks");

        let chunks = mcg.get_chunks_mut();

        let _ = chunks.par_iter_mut().for_each(|c| {
            for y in 0..height {
                for z in 0..CHUNK_LENGTH {
                    let lz = c.0.z * CHUNK_LENGTH as i32 + z as i32;
                    if lz >= length as i32 {
                        continue;
                    }

                    for x in 0..CHUNK_WIDTH {
                        let lx = c.0.x * CHUNK_WIDTH as i32 + x as i32;
                        if lx >= width as i32 {
                            continue;
                        }

                        // magic
                        let i = (y as usize) * (length as usize) * (width as usize)
                            + (lz as usize) * (width as usize)
                            + (lx as usize);

                        let blk =
                            get_internal_block_id(version, &BlockId::Numeric(blocks[i] as u16));

                        match blk {
                            Some(blk) => c.1.set_block(x, y, z, blk),
                            None => {}
                        }
                    }
                }
            }
        });

        Ok(mcg)
    }

    fn get_mcgalaxy_level_file_size(&self) -> usize {
        2 // signature
        + 2 // width
        + 2 // length
        + 2 // height
        + 2 // spawn_x
        + 2 // spawn_z
        + 2 // spawn_y
        + 1 // spawn_yaw
        + 1 // spawn_pitch
        + 1 // min_access_perm
        + 1 // min_build_perm
        + (self.get_block_width() as usize * self.get_block_height() as usize * self.get_block_length() as usize) // block array
    }

    fn write_mcgalaxy_level(&self, version: McVersion) -> Vec<u8> {
        let mut c = Cursor::new(vec![0u8; self.get_mcgalaxy_level_file_size()]);
        c.write_u16::<LittleEndian>(1874u16)
            .expect("Unable to write signature!");

        let width = self.get_block_width();
        let length = self.get_block_length();
        let height = self.get_block_height();

        c.write_i16::<LittleEndian>(width as i16)
            .expect("Unable to write level width!");
        c.write_i16::<LittleEndian>(length as i16)
            .expect("Unable to write level length!");
        c.write_i16::<LittleEndian>(height)
            .expect("Unable to write level height!");
        c.write_i16::<LittleEndian>(self.spawn.x as i16)
            .expect("Unable to write spawn X!");
        c.write_i16::<LittleEndian>(self.spawn.z as i16)
            .expect("Unable to write spawn Z!");
        c.write_i16::<LittleEndian>(self.spawn.y as i16)
            .expect("Unable to write spawn Y!");

        let spawn_yaw = self
            .custom_data
            .get_value::<u8, &str>(metadata::SPAWN_YAW)
            .unwrap_or(0);
        let spawn_pitch = self
            .custom_data
            .get_value::<u8, &str>(metadata::SPAWN_PITCH)
            .unwrap_or(0);

        c.write_u8(spawn_yaw).expect("Unable to write spawn yaw!");
        c.write_u8(spawn_pitch)
            .expect("Unable to write spawn pitch!");

        let min_access_perm = self
            .custom_data
            .get_value::<u8, &str>(metadata::MIN_ACCESS_PERM)
            .unwrap_or(0);
        let min_build_perm = self
            .custom_data
            .get_value::<u8, &str>(metadata::MIN_BUILD_PERM)
            .unwrap_or(0);

        c.write_u8(min_access_perm)
            .expect("Unable to write minimum access permissions!");
        c.write_u8(min_build_perm)
            .expect("Unable to write minimum build permissions!");

        let mut blocks = vec![0u8; width as usize * length as usize * height as usize];

        let mx = self.get_min_block_x();
        let mz = self.get_min_block_z();

        // Write blocks
        blocks.par_iter_mut().enumerate().for_each(|(i, v)| {
            let y = i / (length as usize * width as usize);
            let z = (i / width as usize) % length as usize;
            let x = i % width as usize;

            *v = self.get_block(x as i32 + mx, y as i16, z as i32 + mz) as u8;
        });

        c.write_all(blocks.as_slice()).expect("Block array");

        c.into_inner()
    }
}
