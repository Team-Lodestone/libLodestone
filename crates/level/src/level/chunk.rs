use lodestone_common::types::hashmap_ext::Value;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;

pub const CHUNK_WIDTH: i8 = 16;
pub const CHUNK_LENGTH: i8 = 16;

#[derive(PartialEq, Clone, Serialize, Deserialize)]
pub enum Light {
    BLOCK,
    SKY,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Chunk {
    // Width and depth should always be 16 for our use cases.
    width: i8,
    pub height: i16,
    length: i8,

    // YZX ordering
    pub blocks: Vec<u16>,
    pub data: Vec<u8>,
    pub block_light: Vec<i8>,
    pub sky_light: Vec<i8>,

    pub height_map: Vec<i16>,
    pub block_map: Vec<u16>,

    pub custom_data: HashMap<String, Value>,
}

impl Chunk {
    pub fn new(height: i16) -> Chunk {
        let width: usize = CHUNK_WIDTH as usize;
        let length: usize = CHUNK_LENGTH as usize;
        let height: usize = height as usize;

        Chunk {
            width: width as i8,
            height: height as i16,
            length: length as i8,

            blocks: vec![0u16; width * height * length],
            data: vec![0u8; width * height * length],
            block_light: vec![0i8; width * length],
            sky_light: vec![0i8; width * length],

            height_map: vec![0i16; width * length],
            block_map: vec![0u16; width * length],

            custom_data: Default::default(),
        }
    }

    pub fn generate_heightmap(&self) -> Vec<i16> {
        let mut heightmap: Vec<i16> =
            Vec::with_capacity(CHUNK_WIDTH as usize * CHUNK_LENGTH as usize);
        heightmap.resize(CHUNK_WIDTH as usize * CHUNK_LENGTH as usize, -1);

        for z in 0..CHUNK_LENGTH {
            for x in 0..CHUNK_WIDTH {
                for y in (0..self.height).rev() {
                    let blk = self.get_block(x, y, z);
                    if blk != 0 {
                        heightmap[z as usize * CHUNK_WIDTH as usize + x as usize] =
                            (y + 1).min(self.height - 1);
                        break;
                    }
                }
            }
        }

        heightmap
    }

    pub fn generate_blockmap(&self) -> Vec<u16> {
        let mut blkmap: Vec<u16> = Vec::with_capacity(CHUNK_WIDTH as usize * CHUNK_LENGTH as usize);
        blkmap.resize(CHUNK_WIDTH as usize * CHUNK_LENGTH as usize, 0xFFFF);

        for z in 0..CHUNK_LENGTH {
            for x in 0..CHUNK_WIDTH {
                for y in (0..self.height).rev() {
                    let blk = self.get_block(x, y, z);
                    if !crate::block::get_block(blk)
                        .expect("Get block for blockmap")
                        .is_translucent_map
                    {
                        blkmap[z as usize * CHUNK_WIDTH as usize + x as usize] = blk;
                        break;
                    }
                }
            }
        }

        blkmap
    }

    #[inline(always)]
    pub fn get_index(&self, x: i8, y: i16, z: i8) -> usize {
        (y as usize)
            + (z as usize) * (self.height as usize)
            + (x as usize) * (self.height as usize) * CHUNK_LENGTH as usize // might actually be CHUNK_LENGTH
    }

    pub fn get_block(&self, x: i8, y: i16, z: i8) -> u16 {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.blocks[self.get_index(x, y, z)]
    }

    pub fn set_block(&mut self, x: i8, y: i16, z: i8, block: u16) {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return;
        }

        let i = self.get_index(x, y, z);

        // println!("{}", self.height);
        self.blocks[i] = block;
    }

    pub fn get_data(&self, x: i8, y: i16, z: i8) -> u8 {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.data[self.get_index(x, y, z)]
    }

    pub fn set_state(&mut self, x: i8, y: i16, z: i8, state: u8) {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return;
        }

        let i = self.get_index(x, y, z);

        self.data[i] = state;
    }

    pub fn get_light(&self, light_type: Light, x: i8, y: i16, z: i8) -> i8 {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        if light_type == Light::SKY {
            self.sky_light[self.get_index(x, y, z)]
        } else {
            self.block_light[self.get_index(x, y, z)]
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i8, y: i16, z: i8, mut level: i8) {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return;
        }

        // don't let it overflow past max light level
        if level > 15 {
            level = 15;
        }

        let i = self.get_index(x, y, z);

        if light_type == Light::SKY {
            self.sky_light[i] = level;
        } else {
            self.block_light[i] = level;
        }
    }

    pub fn set_height(&mut self, height: i16) {
        let h = self.height;
        self.height = height;

        let new = (self.width as usize) * (height as usize) * (self.length as usize);

        let mut new_blocks = vec![0; new];
        let mut new_data = vec![0; new];

        for x in 0..self.width {
            for z in 0..self.length {
                for y in 0..h.min(height) {
                    let oi = (y as usize)
                        + (z as usize) * (h as usize)
                        + (x as usize) * (h as usize) * (self.length as usize);
                    let ni = (y as usize)
                        + (z as usize) * (height as usize)
                        + (x as usize) * (height as usize) * (self.length as usize);

                    new_blocks[ni] = self.blocks[oi];
                    new_data[ni] = self.data[oi];
                }
            }
        }

        self.blocks = new_blocks;
        self.data = new_data;
    }
}
