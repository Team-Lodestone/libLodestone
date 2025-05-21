use crate::classic::ClassicLevel;
use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::io::{read_prefixed_2_byte_string, write_prefixed_2_byte_string};
use std::io::{Cursor, Read, Write};
use std::time::SystemTime;
use wasm_bindgen::prelude::*;

#[derive(Debug)]
#[wasm_bindgen(getter_with_clone)]
pub struct MineV2 {
    pub classic_level: ClassicLevel,
    pub version: i8,
    pub name: String,
    pub author: String,
    pub creation_time: i64
}
#[wasm_bindgen]
impl MineV2 {
    #[wasm_bindgen]
    pub fn new(
        width: i16,
        height: i16,
        length: i16,
        name: String,
        author: String
    ) -> MineV2 {
        MineV2 {
            classic_level: ClassicLevel {
                width,
                height,
                length,
                blocks: vec![0u8; (width as usize) * (height as usize) * (length as usize)],
            },
            version: 1,
            name,
            author,
            creation_time: SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).expect("Time since unix epoch").as_millis() as i64,
        }
    }

    pub fn get_byte_size(&self) -> usize {
        let mut size = self.classic_level.get_byte_size(); // classic_level size

        size += 4; // signature
        size += 1; // version
        size += 2 + self.name.len(); // world name
        size += 2 + self.author.len(); // author name
        size += 8; // time created

        size
    }

    #[wasm_bindgen]
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

        if (signature != 0x271BB788) {
            return Err("Signature does not match required '27 1B B7 88'".to_string());
        }

        let mut blocks: Vec<u8> = vec![0; (width as usize) * (length as usize) * (height as usize)];

        c.read_exact(&mut blocks).expect("Failed to read block array");

        Ok(MineV2 {
            classic_level: ClassicLevel {
                width,
                length,
                height,
                blocks,
            },
            version,
            name,
            author,
            creation_time
        })
    }

    #[wasm_bindgen]
    pub fn write(&self, out: &mut [u8]) {
        if (out.len() < self.get_byte_size()) {
            panic!("Output buffer is too small");
        }

        let mut c = Cursor::new(out);

        c.write_i32::<BigEndian>(0x271BB788).expect("Signature write");
        c.write_i8(self.version).expect("Version");
        write_prefixed_2_byte_string(&mut c, &self.name);
        write_prefixed_2_byte_string(&mut c, &self.author);
        c.write_i64::<BigEndian>(self.creation_time).expect("Creation timestamp");
        c.write_i16::<BigEndian>(self.classic_level.width).expect("Width");
        c.write_i16::<BigEndian>(self.classic_level.length).expect("Depth");
        c.write_i16::<BigEndian>(self.classic_level.height).expect("Height");

        c.write_all(self.classic_level.blocks.as_slice()).expect("Block array");
    }
}