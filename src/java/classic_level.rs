use std::fs::File;
use std::io::{Cursor, Read, self, Write};
use std::thread::spawn;
use byteorder::{LittleEndian, ReadBytesExt};
use wasm_bindgen::prelude::*;


// TODO: central Level class that we can inherit
// well actually idk if this will happen, still trying to figure that out...
#[derive(Debug)]
#[wasm_bindgen]
pub struct ClassicLevel {
    width: i16,
    height: i16,
    depth: i16
}

#[derive(Debug)]
#[wasm_bindgen]
pub struct MCGLevel {
    classic_level: ClassicLevel,
    spawn_x: i16,
    spawn_y: i16,
    spawn_z: i16,
    spawn_yaw: u8,
    spawn_pitch: u8,
    min_access_perm: u8,
    min_build_perm: u8,
    blocks: Vec<u8>
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
            },
            spawn_x,
            spawn_y,
            spawn_z,
            spawn_yaw,
            spawn_pitch,
            min_access_perm,
            min_build_perm,
            blocks: vec![0; ((width) * (height) * (depth)) as usize],
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

        let mut blocks: Vec<u8> = vec![0; (w as usize) * (d as usize) * (h as usize)];

        c.read_exact(&mut blocks).expect("Failed to read block array");

        let mcg = MCGLevel {
            classic_level: ClassicLevel {
                width: w,
                depth: d,
                height: h,
            },
            spawn_x,
            spawn_y,
            spawn_z,
            spawn_yaw,
            spawn_pitch,
            min_access_perm,
            min_build_perm,
            blocks
        };

        Ok(mcg)
    }
}