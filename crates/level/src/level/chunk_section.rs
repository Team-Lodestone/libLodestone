use crate::level::chunk::{Light, CHUNK_LENGTH, CHUNK_SECTION_HEIGHT, CHUNK_WIDTH};
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ChunkSection {
    // YZX ordering
    pub blocks: Vec<u16>,
    pub data: Vec<u8>,
    pub block_light: Vec<u8>,
    pub sky_light: Vec<u8>,
}

impl ChunkSection {
    pub fn new() -> ChunkSection {
        ChunkSection {
            blocks: vec![
                0u16;
                CHUNK_WIDTH as usize
                    * CHUNK_SECTION_HEIGHT as usize
                    * CHUNK_LENGTH as usize
            ],
            data: vec![
                0u8;
                CHUNK_WIDTH as usize * CHUNK_SECTION_HEIGHT as usize * CHUNK_LENGTH as usize
            ],
            block_light: vec![
                0u8;
                CHUNK_WIDTH as usize
                    * CHUNK_SECTION_HEIGHT as usize
                    * CHUNK_LENGTH as usize
            ],
            sky_light: vec![
                0u8;
                CHUNK_WIDTH as usize
                    * CHUNK_SECTION_HEIGHT as usize
                    * CHUNK_LENGTH as usize
            ],
        }
    }

    #[inline(always)]
    pub fn get_index(x: i8, y: i16, z: i8) -> usize {
        // y as usize + (z as usize * CHUNK_SECTION_HEIGHT as usize) + (x as usize * CHUNK_SECTION_HEIGHT as usize * CHUNK_LENGTH as usize)
        y as usize * 16 * 16 + z as usize * 16 + x as usize
    }

    pub fn get_block(&self, x: i8, y: i16, z: i8) -> u16 {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return 0;
        }

        match self.blocks.get(Self::get_index(x, y, z)) {
            Some(block) => *block,
            None => 0,
        }
    }

    pub fn set_block(&mut self, x: i8, y: i16, z: i8, block: u16) {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return;
        }

        self.blocks[Self::get_index(x, y, z)] = block;
    }

    pub fn get_state(&self, x: i8, y: i16, z: i8) -> u8 {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return 0;
        }

        self.data[Self::get_index(x, y, z)]
    }

    pub fn set_state(&mut self, x: i8, y: i16, z: i8, state: u8) {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return;
        }

        self.data[Self::get_index(x, y, z)] = state;
    }

    pub fn get_light(&self, light_type: Light, x: i8, y: i16, z: i8) -> u8 {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return 0;
        }

        if light_type == Light::SKY {
            self.sky_light[Self::get_index(x, y, z)]
        } else {
            self.block_light[Self::get_index(x, y, z)]
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i8, y: i16, z: i8, mut level: u8) {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return;
        }

        // don't let it overflow past max light level
        if level > 15 {
            level = 15;
        }

        let i = Self::get_index(x, y, z);

        if light_type == Light::SKY {
            self.sky_light[i] = level;
        } else {
            self.block_light[i] = level;
        }
    }
}
