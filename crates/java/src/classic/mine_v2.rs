use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::io::{read_prefixed_2_byte_string, write_prefixed_2_byte_string};
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::{CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::{metadata, Level};
use rayon::prelude::*;
use std::io::{Cursor, Read, Write};
use std::time::{SystemTime};

pub trait MineV2Level {
    fn new_minev2(width: i16, height: i16, length: i16, name: String, author: String) -> Level;
    fn read_minev2(data: Vec<u8>) -> Result<Level, String>;
    fn write_minev2(&mut self, out: &mut [u8]);
    fn get_minev2_file_size(&self) -> usize;
}

impl MineV2Level for Level {
    fn new_minev2(width: i16, height: i16, length: i16, name: String, author: String) -> Level {
        let mut level = Level::new_with_name(name);
        level.create_finite(width as i32, height, length as i32);

        level
            .custom_data
            .set_value(metadata::AUTHOR.to_string(), author);
        level.custom_data.set_value(
            metadata::CREATION_TIME.to_string(),
            SystemTime::now()
                .duration_since(SystemTime::UNIX_EPOCH)
                .expect("Time since unix epoch")
                .as_millis() as i64,
        );

        level
    }

    fn read_minev2(data: Vec<u8>) -> Result<Level, String> {
        let mut c = Cursor::new(data);
        let signature = c.read_u32::<BigEndian>().expect("Signature");
        let version = c.read_i8().expect("Version");
        if version != 1 { panic!("This method only reads .Mine V2 files.") }
        
        let name = read_prefixed_2_byte_string(&mut c);
        let author = read_prefixed_2_byte_string(&mut c);
        let creation_time = c.read_i64::<BigEndian>().expect("Creation time");
        let width = c.read_i16::<BigEndian>().expect("Width");
        let length = c.read_i16::<BigEndian>().expect("Depth");
        let height = c.read_i16::<BigEndian>().expect("Height");

        log::debug!("w: {}, d: {}, h: {}", width, length, height);
        log::debug!("World name: {}", name);
        log::debug!("Author: {}", author);

        if signature != 0x271BB788 {
            return Err("Signature does not match required '27 1B B7 88'".to_string());
        }

        let mut blocks: Vec<u8> = vec![0; (width as usize) * (length as usize) * (height as usize)];

        c.read_exact(&mut blocks)
            .expect("Failed to read block array");

        let mut level = Level::new_with_name(name);

        level
            .custom_data
            .set_value(metadata::AUTHOR.to_string(), author);
        level
            .custom_data
            .set_value(metadata::CREATION_TIME.to_string(), creation_time);

        level.create_finite(width as i32, height, length as i32);

        log::debug!("Read into chunks");
        // let s = Instant::now();

        let chunks = level.get_chunks_mut();

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

                        c.1.blocks[(y as usize)
                            + (z as usize) * (height as usize)
                            + (x as usize) * (height as usize) * CHUNK_LENGTH as usize] =
                            blocks[i] as u16;
                    }
                }
            }
        });

        // println!("Done reading into chunks in {:?}", s.elapsed());

        Ok(level)
    }

    fn write_minev2(&mut self, out: &mut [u8]) {
        if out.len() < self.get_minev2_file_size() {
            panic!("Output buffer is too small");
        }

        let mut c = Cursor::new(out);

        c.write_i32::<BigEndian>(0x271BB788)
            .expect("Signature write");
        c.write_i8(1).expect("Version");
        write_prefixed_2_byte_string(&mut c, &self.name);
        write_prefixed_2_byte_string(
            &mut c,
            &self
                .custom_data
                .get_value::<String, _>(metadata::AUTHOR)
                .unwrap_or("Unknown".to_string()),
        );
        c.write_i64::<BigEndian>(
            self.custom_data
                .get_value(metadata::CREATION_TIME)
                .unwrap_or(0),
        )
        .expect("Creation timestamp");

        let width = self.get_block_width() as usize;
        let depth = self.get_block_length() as usize;
        let height = self.get_block_height() as usize;

        let mx = self.get_min_block_x();
        let mz = self.get_min_block_z();

        c.write_i16::<BigEndian>(width as i16).expect("Width");
        c.write_i16::<BigEndian>(depth as i16).expect("Depth");
        c.write_i16::<BigEndian>(height as i16).expect("Height");

        let mut blocks = vec![0u8; width * height * depth];

        blocks.par_iter_mut().enumerate().for_each(|(i, v)| {
            let y = i / (depth * width);
            let z = (i / width) % depth;
            let x = i % width;

            *v = self.get_block(x as i32 + mx, y as i16, z as i32 + mz) as u8;
        });

        c.write_all(blocks.as_slice()).expect("Block array");
    }

    fn get_minev2_file_size(&self) -> usize {
        let mut size = 4; // signature
        size += 1; // version
        size += 2 + self.name.len(); // world name
        size += 2 + self
            .custom_data
            .get_value::<String, _>(metadata::AUTHOR)
            .unwrap_or("Unknown".to_string())
            .len(); // author name
        size += 8; // time created
        size += 2; // width
        size += 2; // length
        size += 2; // height

        size += (self.get_block_width() as usize)
            * (self.get_block_height() as usize)
            * (self.get_block_length() as usize);

        size
    }
}
