use std::any::Any;

#[derive(PartialEq)]
pub enum Light {
    BLOCK,
    SKY,
}

pub struct Chunk {
    // Width and depth should always be 16 for our use cases.
    width: i8,
    pub height: i16,
    depth: i8,

    // YZX ordering
    pub blocks: Vec<u16>,
    pub data: Vec<u8>,
    pub block_light: Vec<u8>,
    pub sky_light: Vec<u8>,

    pub height_map: Vec<u16>,
    pub block_map: Vec<u16>,
    pub custom_data: Vec<std::collections::HashMap<String, Box<dyn Any>>>,
}

impl Chunk {
    pub fn generate_heightmap(&self) -> Vec<i16> {
        let mut heightmap: Vec<i16> = Vec::with_capacity(16 * 16);

        for z in 0..16 {
            for x in 0..16 {
                for y in (0..self.height).rev() {
                    let blk = self.get_block(x, y, z);
                    if blk != 0 {
                        heightmap.push((y + 1).min(self.height - 1));
                        break;
                    }
                }
            }
        }

        heightmap
    }

    pub fn generate_blockmap(&self) -> Vec<u16> {
        let mut blkmap: Vec<u16> = Vec::with_capacity(16 * 16);

        for z in 0..16 {
            for x in 0..16 {
                for y in (0..self.height).rev() {
                    let blk = self.get_block(x, y, z);
                    if !crate::block::get_block(blk)
                        .expect("Get block for blockmap")
                        .is_translucent_map
                    {
                        blkmap.push(blk);
                        break;
                    }
                }
            }
        }

        blkmap
    }

    pub fn get_index(x: i8, y: i16, z: i8) -> usize {
        (y as usize) + (z as usize) * 128 + (x as usize) * 128 * 16
    }

    pub fn get_block(&self, x: i8, y: i16, z: i8) -> u16 {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.blocks[Chunk::get_index(x, y, z)]
    }

    pub fn set_block(&mut self, x: i8, y: i16, z: i8, block: u16) {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return;
        }

        self.blocks[Chunk::get_index(x, y, z)] = block;
    }

    pub fn get_data(&self, x: i8, y: i16, z: i8) -> u8 {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.data[Chunk::get_index(x, y, z)]
    }

    pub fn set_state(&mut self, x: i8, y: i16, z: i8, state: u8) {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return;
        }

        self.data[Chunk::get_index(x, y, z)] = state;
    }

    pub fn get_light(&self, light_type: Light, x: i8, y: i16, z: i8) -> u8 {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        if light_type == Light::SKY {
            self.sky_light[Chunk::get_index(x, y, z)]
        } else {
            self.block_light[Chunk::get_index(x, y, z)]
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i8, y: i16, z: i8, mut level: u8) {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return;
        }

        // don't let it overflow past max light level
        if level > 15 {
            level = 15;
        }

        if light_type == Light::SKY {
            self.sky_light[Chunk::get_index(x, y, z)] = level;
        } else {
            self.block_light[Chunk::get_index(x, y, z)] = level;
        }
    }
}
