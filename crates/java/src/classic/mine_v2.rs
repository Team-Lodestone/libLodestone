use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::io::{read_prefixed_2_byte_string, write_prefixed_2_byte_string};
use std::io::{Cursor, Read, Write};
use std::time::SystemTime;
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::{metadata, Level};

pub trait MineV2Level {
    fn new_minev2(
        width: i16,
        height: i16,
        length: i16,
        name: String,
        author: String
    ) -> Level;
    fn read_minev2(data: Vec<u8>) -> Result<Level, String>;
    fn write_minev2(&mut self, out: &mut [u8]);
    fn get_minev2_file_size(&self) -> usize;
}

impl MineV2Level for Level {
    fn new_minev2(
        width: i16,
        height: i16,
        length: i16,
        name: String,
        author: String
    ) -> Level {
        let mut level = Level::new_with_name(name);
        level.create_finite(width as i32, height, length as i32);

        level.custom_data.set_value(metadata::AUTHOR.to_string(), author);
        level.custom_data.set_value(metadata::CREATION_TIME.to_string(), SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).expect("Time since unix epoch").as_millis() as i64);

        level
    }

    fn read_minev2(data: Vec<u8>) -> Result<Level, String> {
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

        level.custom_data.set_value(metadata::AUTHOR.to_string(), author);
        level.custom_data.set_value(metadata::CREATION_TIME.to_string(), creation_time);

        level.create_finite(width as i32, height, length as i32);

        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    level.set_block(x as i32, y, z as i32, blocks[(y as usize) * ((length as usize) * (width as usize)) + (z as usize) * (width as usize) + (x as usize)] as u16);
                }
            }
        }

        Ok(level)
    }

    fn write_minev2(&mut self, out: &mut [u8]) {
       if out.len() < self.get_minev2_file_size() {
           panic!("Output buffer is too small");
       }

       let mut c = Cursor::new(out);

       c.write_i32::<BigEndian>(0x271BB788).expect("Signature write");
       c.write_i8(1).expect("Version");
       write_prefixed_2_byte_string(&mut c, &self.name);
       write_prefixed_2_byte_string(&mut c, &self.custom_data.get_value::<String, _>(metadata::AUTHOR).unwrap_or("Project Lodestone User".to_string()));
       c.write_i64::<BigEndian>(self.custom_data.get_value(metadata::CREATION_TIME).unwrap_or(0)).expect("Creation timestamp");

       let width = self.get_block_width() as usize;
       let depth = self.get_block_depth() as usize;
       let height = self.get_block_height() as usize;

       c.write_i16::<BigEndian>(width as i16).expect("Width");
       c.write_i16::<BigEndian>(depth as i16).expect("Depth");
       c.write_i16::<BigEndian>(height as i16).expect("Height");

       let mut blocks: Vec<u8> = Vec::new();
       blocks.resize(width * height * depth, 0);

       for y in 0..height {
           for z in 0..depth {
               for x in 0..width {
                   blocks[(y) * (depth * width) + (z) * (width) + (x)] = self.get_block(x as i32, y as i16, z as i32) as u8;
               }
           }
       }

       c.write_all(blocks.as_slice()).expect("Block array");
   }

    fn get_minev2_file_size(&self) -> usize {
        let mut size = 4; // signature
        size += 1; // version
        size += 2 + self.name.len(); // world name
        size += 2 + self.custom_data.get_value::<String, _>(metadata::AUTHOR).unwrap_or("Project Lodestone User".to_string()).len(); // author name
        size += 8; // time created
        size += 2; // width
        size += 2; // length
        size += 2; // height

        size += (self.get_block_width() as usize) * (self.get_block_height() as usize) * (self.get_block_depth() as usize);

        size
    }
}
