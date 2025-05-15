use std::collections::HashMap;
use crate::java::classic::ClassicLevel;
use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use std::io::{Cursor, Read, Write};
use std::ptr::null;
use wasm_bindgen::prelude::*;

// IMPORTANT: there can be extra data after the block array due to extensions to the format made by both the server software and plugins.
#[derive(Debug)]
#[wasm_bindgen(getter_with_clone)]
pub struct MCGLevel {
    pub classic_level: ClassicLevel,
    pub spawn_x: i16,
    pub spawn_y: i16,
    pub spawn_z: i16,
    pub spawn_yaw: u8,
    pub spawn_pitch: u8,
    pub min_access_perm: u8,
    pub min_build_perm: u8,

    section_width: i16,
    section_depth: i16,
    pub custom_block_sections: Vec<Vec<u8>>,
}

static READ_BLOCK_MAPPINGS: HashMap<u8, u16> = HashMap::from([
    (163, 256),
    (198, 512),
    (199, 768)
]);
static WRITE_BLOCK_MAPPINGS: HashMap<u16, u8> = HashMap::from([
    (0, 0),
    (1, 163),
    (2, 198),
    (3, 199)
]);

#[wasm_bindgen]
impl MCGLevel {
    #[wasm_bindgen]
    pub fn new(
        width: i16,
        height: i16,
        depth: i16,
        spawn_x: i16,
        spawn_y: i16,
        spawn_z: i16,
        spawn_yaw: u8,
        spawn_pitch: u8,
        min_access_perm: u8,
        min_build_perm: u8,
    ) -> MCGLevel {
        let section_width = (width as f32 / 16).ceil() as i16;
        let section_height = (height as f32 / 16).ceil() as i16;
        let section_depth = (depth as f32 / 16).ceil() as i16;
        MCGLevel {
            classic_level: ClassicLevel {
                width,
                height,
                depth,
                blocks: vec![0u8; (width as usize) * (height as usize) * (depth as usize)],
            },
            spawn_x,
            spawn_y,
            spawn_z,
            spawn_yaw,
            spawn_pitch,
            min_access_perm,
            min_build_perm,

            section_width,
            section_depth,
            custom_block_sections: vec![null(); (section_width * section_height * section_depth) as usize],
        }
    }

    #[wasm_bindgen]
    pub fn new_from_data(data: Vec<u8>) -> Result<MCGLevel, String> {
        let mut c = Cursor::new(data); // literally just array with position ig
        let signature = c.read_u16::<LittleEndian>().unwrap();
        let w = c.read_i16::<LittleEndian>().unwrap();
        let d = c.read_i16::<LittleEndian>().unwrap();
        let h = c.read_i16::<LittleEndian>().unwrap();
        let spawn_x = c.read_i16::<LittleEndian>().unwrap();
        let spawn_z = c.read_i16::<LittleEndian>().unwrap();
        let spawn_y = c.read_i16::<LittleEndian>().unwrap();
        let spawn_yaw = c.read_u8().unwrap();
        let spawn_pitch = c.read_u8().unwrap();

        println!("sig: {}", signature);
        // note: not required to be 1874 apparently.
        // although why wouldn't it be?
        if (signature != 1874) {
            return Err("Signature does not match required '1874'".to_string());
        }

        let min_access_perm = c.read_u8().unwrap();
        let min_build_perm = c.read_u8().unwrap();

        println!("w: {}, h: {}, d: {}", w, d, h);
        println!("spX: {}, spY: {}, spZ: {}", spawn_x, spawn_y, spawn_z);

        // TODO: I think there's a performance issue with loading the blocks...
        let mut blocks: Vec<u8> = vec![0; (w as usize) * (d as usize) * (h as usize)];

        c.read_exact(&mut blocks).expect("Failed to read block array");

        let section_width = (w as f32 / 16).ceil() as i32;
        let section_height = (h as f32 / 16).ceil() as i32;
        let section_depth = (d as f32 / 16).ceil() as i32;

        let mut custom_block_sections: Vec<Vec<u8>> = vec![null(); (section_width * section_height * section_depth) as usize];

        if c.read_u8().unwrap() == 0xBD {
            for y in 0..section_height {
                for z in 0..section_depth {
                    for x in 0..section_width {
                        let b = c.read_u8().unwrap();

                        if b == 1 {
                            let section_index = (y * section_depth + z) * section_width + x;
                            let mut section: Vec<u8> = vec![0; 4096];

                            c.read_exact(&mut section).expect(format!("Failed to read section {x} {y} {z}"));
                            custom_block_sections[section_index] = section;
                        }
                    }
                }
            }
        }

        let mcg = MCGLevel {
            classic_level: ClassicLevel {
                width: w,
                depth: d,
                height: h,
                blocks,
            },
            spawn_x,
            spawn_y,
            spawn_z,
            spawn_yaw,
            spawn_pitch,
            min_access_perm,
            min_build_perm,

            section_width,
            section_depth,
            custom_block_sections
        };

        Ok(mcg)
    }

    #[wasm_bindgen]
    pub fn set_world_spawn(&mut self, x: i16, y: i16, z: i16) {
        self.spawn_x = x;
        self.spawn_y = y;
        self.spawn_z = z;
    }

    #[wasm_bindgen]
    pub fn set_world_spawn_rot(&mut self, yaw: u8, pitch: u8) {
        self.spawn_yaw = yaw;
        self.spawn_pitch = pitch;
    }
    
    pub fn get_block(&mut self, x: i16, y: i16, z: i16) -> u16 {
        let index = (y * self.classic_level.depth + z) * self.classic_level.width + x;
        let block = self.classic_level.blocks[index as usize];

        if READ_BLOCK_MAPPINGS.contains_key(&block) {
            return READ_BLOCK_MAPPINGS[block] | self.get_ext_block(x, y, z) as u16;
        }

        block as u16
    }

    fn get_ext_block(&mut self, x: i16, y: i16, z: i16) -> u8 {
        let section_x = x >> 4;
        let section_y = y >> 4;
        let section_z = z >> 4;

        let index = (section_y * self.section_depth + section_z) * self.section_width + section_x;
        let section = &self.custom_block_sections[index as usize];
        if !section.is_null() {
            return *section[(y & 15) << 8 | (z & 15) << 4 | (x & 15)];
        }

        0
    }
    
    pub fn set_block(&mut self, x: i16, y: i16, z: i16, block: i16) {
        let index = (y * self.classic_level.depth + z) * self.classic_level.width + x;

        if block >= 256 {
            self.classic_level.blocks[index as usize] = WRITE_BLOCK_MAPPINGS[block];
            self.set_ext_block(x, y, z, block);
        } else {
            self.classic_level.blocks[index as usize] = block as u8;
        }
    }

    fn set_ext_block(&mut self, x: i16, y: i16, z: i16, block: i16) {
        let section_x = x >> 4;
        let section_y = y >> 4;
        let section_z = z >> 4;

        let index = (section_y * self.section_depth + section_z) * self.section_width + section_x;
        let section = &self.custom_block_sections[index as usize];

        if !section.is_null() {
            let new_section = vec![0; 4096];
            self.custom_block_sections[index as usize] = new_section;
        }

        *section[(y & 15) << 8 | (z & 15) << 4 | (x & 15)] = block & 0xFF;
    }

    #[wasm_bindgen]
    pub fn write(&self, out: &mut [u8]) {
        if (out.len() < 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1 + self.classic_level.blocks.len()) {
            panic!("Output buffer is too small");
        }

        let mut c = Cursor::new(out);

        c.write_i16::<LittleEndian>(1874).expect("Signature write");
        c.write_i16::<LittleEndian>(self.classic_level.width).expect("Width write");
        c.write_i16::<LittleEndian>(self.classic_level.depth).expect("Depth write");
        c.write_i16::<LittleEndian>(self.classic_level.height).expect("Height write");
        c.write_i16::<LittleEndian>(self.spawn_x).expect("SpawnX write");
        c.write_i16::<LittleEndian>(self.spawn_z).expect("SpawnZ write");
        c.write_i16::<LittleEndian>(self.spawn_y).expect("SpawnY write");
        c.write_u8(self.spawn_yaw).expect("Spawn Yaw write");
        c.write_u8(self.spawn_pitch).expect("Spawn Pitch write");
        c.write_u8(self.min_access_perm).expect("Min Access Perm write");
        c.write_u8(self.min_build_perm).expect("Min Build Perm write");

        c.write_all(&self.classic_level.blocks).expect("Blocks write");
    }
}