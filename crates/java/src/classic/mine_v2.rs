use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::io::{read_prefixed_2_byte_string, write_prefixed_2_byte_string};
use std::io::{Cursor, Read, Write};
use std::time::SystemTime;
use wasm_bindgen::prelude::*;
use lodestone_level::level::level::Level;
use std::collections::HashMap;
use lodestone_level::level::chunk::Chunk;
use lodestone_level::level::level::Coords;

#[derive(Debug)]
pub struct MineV2 {
    pub level: Level,
    pub version: i8,
    pub author: String,
    pub creation_time: i64,
}

impl MineV2 {
    pub fn new(
        width: i16,
        height: i16,
        length: i16,
        name: String,
        author: String
    ) -> MineV2 {
        MineV2 {
            level: Level::new_with_name(name),
            version: 1,
            author,
            creation_time: SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).expect("Time since unix epoch").as_millis() as i64,
        }
    }

    pub fn get_byte_size(&self) -> usize {
        let mut size = 4; // signature
        size += 1; // version
        size += 2 + self.level.name.len(); // world name
        size += 2 + self.author.len(); // author name
        size += 8; // time created
        size += 2; // width
        size += 2; // length
        size += 2; // height

        size += (self.level.get_block_width() as usize) * (self.level.get_block_height() as usize) * (self.level.get_block_depth() as usize);

        println!("w: {}, d: {}, h: {}", self.level.get_block_width(), self.level.get_block_height(), self.level.get_block_depth());

        size
    }

    pub fn new_from_data(data: Vec<u8>) -> Result<MineV2, String> {
        let mut c = Cursor::new(data);
        let signature = c.read_u32::<BigEndian>().expect("Signature");
        let version = c.read_i8().expect("Version");
        let name = read_prefixed_2_byte_string(&mut c);
        let author = read_prefixed_2_byte_string(&mut c);
        let creation_time = c.read_i64::<BigEndian>().expect("Creation time");
        let width = c.read_i16::<BigEndian>().expect("Width");
        let length = c.read_i16::<BigEndian>().expect("Depth");
        let height = c.read_i16::<BigEndian>().expect("Height");

        println!("w: {}, d: {}, h: {}", width, length, height);
        println!("World name: {}", name);
        println!("Author: {}", author);

        if signature != 0x271BB788 {
            return Err("Signature does not match required '27 1B B7 88'".to_string());
        }

        let mut blocks: Vec<u8> = vec![0; (width as usize) * (length as usize) * (height as usize)];

        c.read_exact(&mut blocks).expect("Failed to read block array");

        let mut level = Level::new();

        for cx in 0..((width as usize) / 16) {
            for cz in 0..((length as usize) / 16) {
                let coords = Coords { x: cx as i32, z: cz as i32 };
                let chunk = Chunk::new(height);

                level.add_chunk(coords.clone(), chunk);
            }
        }

        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    level.set_block(x as i32, y, z as i32, blocks[(y as usize) * ((length as usize) * (width as usize)) + (z as usize) * (width as usize) + (x as usize)] as u16);
                }
            }
        }

        Ok(MineV2 {
            level,
            version,
            author,
            creation_time
        })
    }

    pub fn write(&mut self, out: &mut [u8]) {
        if out.len() < self.get_byte_size() {
            panic!("Output buffer is too small");
        }

        let mut c = Cursor::new(out);

        c.write_i32::<BigEndian>(0x271BB788).expect("Signature write");
        c.write_i8(self.version).expect("Version");
        write_prefixed_2_byte_string(&mut c, &self.level.name);
        write_prefixed_2_byte_string(&mut c, &self.author);
        c.write_i64::<BigEndian>(self.creation_time).expect("Creation timestamp");

        let width = self.level.get_block_width() as usize;
        let depth = self.level.get_block_depth() as usize;
        let height = self.level.get_block_height() as usize;

        c.write_i16::<BigEndian>(width as i16).expect("Width");
        c.write_i16::<BigEndian>(depth as i16).expect("Depth");
        c.write_i16::<BigEndian>(height as i16).expect("Height");

        let mut blocks: Vec<u8> = Vec::new();
        blocks.resize(width * height * depth, 0);

        for y in 0..height {
            for z in 0..depth {
                for x in 0..width {
                    blocks[(y) * (depth * width) + (z) * (width) + (x)] = self.level.get_block(x as i32, y as i16, z as i32) as u8;
                }
            }
        }

        c.write_all(blocks.as_slice()).expect("Block array");
    }
}