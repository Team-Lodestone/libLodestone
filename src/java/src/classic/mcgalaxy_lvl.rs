use crate::classic::ClassicLevel;
use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use std::io::{Cursor, Read, Write};
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
    custom_block_sections: Vec<Vec<u8>>,
}

//HACK: HORRIBLE!!!
static READ_BLOCK_MAPPINGS: [u16; 256] = [
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 512, 768, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
];
static WRITE_BLOCK_MAPPINGS: [u8; 4] = [0, 163, 198, 199];

#[wasm_bindgen]
impl MCGLevel {
    #[wasm_bindgen]
    pub fn new(
        width: i16,
        height: i16,
        length: i16,
        spawn_x: i16,
        spawn_y: i16,
        spawn_z: i16,
        spawn_yaw: u8,
        spawn_pitch: u8,
        min_access_perm: u8,
        min_build_perm: u8,
    ) -> MCGLevel {
        let section_width = (width as f32 / 16.0).ceil() as i16;
        let section_height = (height as f32 / 16.0).ceil() as i16;
        let section_depth = (length as f32 / 16.0).ceil() as i16;
        MCGLevel {
            classic_level: ClassicLevel {
                width,
                height,
                length,
                blocks: vec![0u8; (width as usize) * (height as usize) * (length as usize)],
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
            custom_block_sections: vec![
                vec![0u8; 0];
                ((section_width as usize) * (section_height as usize) * (section_depth as usize))
                    as usize
            ],
        }
    }

    #[wasm_bindgen]
    pub fn resize(&mut self, width: i16, depth: i16, height: i16) {
        let x0 = self.classic_level.width as usize;
        let z0 = self.classic_level.length as usize;
        let y0 = self.classic_level.height as usize;

        // hate usize
        let x1 = width as usize;
        let z1 = depth as usize;
        let y1 = height as usize;

        let mut blocks = vec![0; x1 * z1 * y1];
        // can't wait for the order to change between every edition of minecraft
        for x in 0..x0.min(x1) {
            for z in 0..z0.min(z1) {
                for y in 0..y0.min(y1) {
                    let p0 = x + x0 * (z + y * z0);
                    let p1 = x + x1 * (z + y * z1);
                    blocks[p1] = self.classic_level.blocks[p0];
                }
            }
        }

        self.classic_level.blocks = blocks;
        self.classic_level.width = x1 as i16;
        self.classic_level.length = z1 as i16;
        self.classic_level.height = y1 as i16;
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
        if signature != 1874 {
            return Err("Signature does not match required '1874'".to_string());
        }

        let min_access_perm = c.read_u8().unwrap();
        let min_build_perm = c.read_u8().unwrap();

        println!("w: {}, h: {}, d: {}", w, d, h);
        println!("spX: {}, spY: {}, spZ: {}", spawn_x, spawn_y, spawn_z);

        // TODO: I think there's a performance issue with loading the blocks...
        let mut blocks: Vec<u8> = vec![0; (w as usize) * (d as usize) * (h as usize)];

        c.read_exact(&mut blocks)
            .expect("Failed to read block array");

        let section_width = (w as f32 / 16.0).ceil() as i16;
        let section_height = (h as f32 / 16.0).ceil() as i16;
        let section_depth = (d as f32 / 16.0).ceil() as i16;

        let mut custom_block_sections: Vec<Vec<u8>> =
            vec![
                vec![0u8; 0];
                (section_width as usize) * (section_height as usize) * (section_depth as usize)
            ];

        if c.read_u8().unwrap() == 0xBD {
            for y in 0..section_height {
                for z in 0..section_depth {
                    for x in 0..section_width {
                        let b = c.read_u8().unwrap();

                        if b == 1 {
                            let section_index =
                                ((y * section_depth + z) * section_width + x) as usize;
                            let mut section: Vec<u8> = vec![0u8; 4096];

                            c.read_exact(&mut section)
                                .expect(format!("Failed to read section {x} {y} {z}").as_str());
                            custom_block_sections[section_index] = section;
                        }
                    }
                }
            }
        }

        let mcg = MCGLevel {
            classic_level: ClassicLevel {
                width: w,
                length: d,
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
            custom_block_sections,
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

    #[wasm_bindgen]
    pub fn get_block(&mut self, x: i16, y: i16, z: i16) -> u16 {
        let index = self.get_index(x, y, z);
        if index == !0 {
            return 0;
        }

        let block = self.classic_level.blocks[index];

        if READ_BLOCK_MAPPINGS[block as usize] != 0 {
            return READ_BLOCK_MAPPINGS[block as usize] | self.get_ext_block(x, y, z) as u16;
        }

        block as u16
    }

    fn get_ext_block(&mut self, x: i16, y: i16, z: i16) -> u8 {
        let section_x = x >> 4;
        let section_y = y >> 4;
        let section_z = z >> 4;

        let index = (section_y * self.section_depth + section_z) * self.section_width + section_x;
        let section = &self.custom_block_sections[index as usize];
        if !section.is_empty() {
            return section[((y & 15) << 8 | (z & 15) << 4 | (x & 15)) as usize];
        }

        0
    }

    #[wasm_bindgen]
    pub fn set_block(&mut self, x: i16, y: i16, z: i16, block: i16) {
        let mut set = block as u8;

        if block >= 256 {
            set = WRITE_BLOCK_MAPPINGS[(block >> 8) as usize];
            self.set_ext_block(x, y, z, (block & 0xFF) as u8);
        }

        let index = self.get_index(x, y, z);
        if index == !0 {
            return;
        }

        self.classic_level.blocks[index] = set;
    }

    fn set_ext_block(&mut self, x: i16, y: i16, z: i16, block: u8) {
        let section_x = x >> 4;
        let section_y = y >> 4;
        let section_z = z >> 4;

        let index = ((section_y * self.section_depth + section_z) * self.section_width + section_x)
            as usize;
        let mut section = &mut self.custom_block_sections[index];

        if !section.is_empty() {
            let new_section = vec![0u8; 4096];
            self.custom_block_sections[index] = new_section;

            section = &mut self.custom_block_sections[index];
        }

        section[((y & 15) << 8 | (z & 15) << 4 | (x & 15)) as usize] = block;
    }

    pub fn calc_section_length(&self) -> usize {
        let mut len = self.custom_block_sections.len();

        for s in self.custom_block_sections.iter() {
            if !s.is_empty() {
                len += s.len();
            }
        }

        len
    }

    #[wasm_bindgen]
    pub fn write(&self, out: &mut [u8]) {
        if out.len()
            < 2 + 2
            + 2
            + 2
            + 2
            + 2
            + 2
            + 1
            + 1
            + 1
            + 1
            + 1
            + self.classic_level.blocks.len()
            + self.calc_section_length()
        {
            panic!("Output buffer is too small");
        }

        let mut c = Cursor::new(out);

        c.write_i16::<LittleEndian>(1874).expect("Signature write");
        c.write_i16::<LittleEndian>(self.classic_level.width)
            .expect("Width write");
        c.write_i16::<LittleEndian>(self.classic_level.length)
            .expect("Depth write");
        c.write_i16::<LittleEndian>(self.classic_level.height)
            .expect("Height write");
        c.write_i16::<LittleEndian>(self.spawn_x)
            .expect("SpawnX write");
        c.write_i16::<LittleEndian>(self.spawn_z)
            .expect("SpawnZ write");
        c.write_i16::<LittleEndian>(self.spawn_y)
            .expect("SpawnY write");
        c.write_u8(self.spawn_yaw).expect("Spawn Yaw write");
        c.write_u8(self.spawn_pitch).expect("Spawn Pitch write");
        c.write_u8(self.min_access_perm)
            .expect("Min Access Perm write");
        c.write_u8(self.min_build_perm)
            .expect("Min Build Perm write");

        c.write_all(&self.classic_level.blocks)
            .expect("Blocks write");

        c.write_u8(0xBD).expect("Custom block section start");
        for s in self.custom_block_sections.iter() {
            if s.is_empty() {
                c.write_u8(0).unwrap();
            } else {
                c.write_u8(1).unwrap();
                c.write_all(s).expect("Custom block section");
            }
        }
    }

    #[wasm_bindgen]
    pub fn get_index(&self, x: i16, y: i16, z: i16) -> usize {
        let x = x as usize;
        let y = y as usize;
        let z = z as usize;

        let w = self.classic_level.width as usize;
        let d = self.classic_level.length as usize;
        let h = self.classic_level.height as usize;

        if x < 0 || y < 0 || z < 0 || x >= w || y >= h || z >= d {
            return !0;
        }

        x + z * w + y * w * d
    }
}
