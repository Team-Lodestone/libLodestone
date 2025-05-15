use crate::java::classic::ClassicLevel;
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
}

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