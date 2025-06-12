use crate::level::chunk_section::ChunkSection;
use lodestone_common::types::hashmap_ext::Value;
use rayon::iter::ParallelIterator;
use rayon::prelude::IntoParallelRefIterator;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;

pub const CHUNK_WIDTH: i8 = 16;
pub const CHUNK_LENGTH: i8 = 16;
pub const CHUNK_SECTION_HEIGHT: i8 = 16;

#[derive(PartialEq, Clone, Serialize, Deserialize)]
pub enum Light {
    BLOCK,
    SKY,
}

#[derive(Clone)]
pub struct Chunk {
    // Width and depth should always be 16 for our use cases.
    width: i8,
    pub height: i16, // TODO: we can remove this due to the presence of sections (likely, we need to figure out finite worlds though)
    length: i8,

    pub chunk_sections: Vec<ChunkSection>,

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

            chunk_sections: Vec::with_capacity(height / CHUNK_SECTION_HEIGHT as usize),

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

    #[inline(always)]
    pub fn get_chunk_section(&self, y: i16) -> Option<&ChunkSection> {
        self.chunk_sections
            .get((y / CHUNK_SECTION_HEIGHT as i16) as usize)
    }

    #[inline(always)]
    pub fn get_chunk_section_mut(&mut self, y: i16) -> Option<&mut ChunkSection> {
        self.chunk_sections
            .get_mut((y / CHUNK_SECTION_HEIGHT as i16) as usize)
    }

    #[inline(always)]
    pub fn get_chunk_section_mut_i(&mut self, i: i16) -> Option<&mut ChunkSection> {
        self.chunk_sections.get_mut(i as usize)
    }

    #[inline(always)]
    pub fn get_or_create_chunk_section_mut_i(&mut self, index: i16) -> &mut ChunkSection {
        println!("i: {}", index);

        if self.get_chunk_section_mut_i(index).is_none() {
            if index >= self.chunk_sections.len() as i16 {
                self.chunk_sections
                    .resize_with((index + 1) as usize, ChunkSection::new);
            }

            self.chunk_sections
                .insert(index as usize, ChunkSection::new());
        }

        self.chunk_sections.get_mut(index as usize).unwrap()
    }

    #[inline(always)]
    pub fn get_or_create_chunk_section_mut(&mut self, y: i16) -> &mut ChunkSection {
        let index = (y / CHUNK_SECTION_HEIGHT as i16) as usize;

        if self.get_chunk_section(y).is_none() {
            if index >= self.chunk_sections.len() {
                self.chunk_sections
                    .resize_with(index + 1, ChunkSection::new);
            }

            self.chunk_sections.insert(index, ChunkSection::new());
        }

        self.chunk_sections.get_mut(index).unwrap()
    }

    #[inline(always)]
    pub fn get_block(&self, x: i8, y: i16, z: i8) -> u16 {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        match self.get_chunk_section(y) {
            Some(s) => s.get_block(x, y % CHUNK_SECTION_HEIGHT as i16, z),
            None => 0,
        }
    }

    #[inline(always)]
    pub fn set_block(&mut self, x: i8, y: i16, z: i8, block: u16) {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return;
        }

        match self.get_chunk_section_mut(y) {
            Some(s) => s.set_block(x, y % CHUNK_SECTION_HEIGHT as i16, z, block),
            _ => {
                if block == 0 {
                    return;
                } // if block is zero we don't want to create new section for lower memory usage

                let cs = self.get_or_create_chunk_section_mut(y);
                cs.set_block(x, y % CHUNK_SECTION_HEIGHT as i16, z, block);
            }
        }
    }

    pub fn get_state(&self, x: i8, y: i16, z: i8) -> u8 {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        match self.get_chunk_section(y) {
            Some(s) => s.get_state(x, y % CHUNK_SECTION_HEIGHT as i16, z),
            None => 0,
        }
    }

    pub fn set_state(&mut self, x: i8, y: i16, z: i8, state: u8) {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return;
        }

        match self.get_chunk_section_mut(y) {
            Some(s) => s.set_state(x, y % CHUNK_SECTION_HEIGHT as i16, z, state),
            _ => {}
        }
    }

    pub fn get_light(&self, light_type: Light, x: i8, y: i16, z: i8) -> u8 {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        match self.get_chunk_section(y) {
            Some(s) => {
                if light_type == Light::SKY {
                    s.get_light(light_type, x, y % CHUNK_SECTION_HEIGHT as i16, z)
                } else {
                    s.get_light(light_type, x, y % CHUNK_SECTION_HEIGHT as i16, z)
                }
            }
            None => 0,
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i8, y: i16, z: i8, level: u8) {
        if x > CHUNK_WIDTH || y > self.height || z > CHUNK_LENGTH || x < 0 || y < 0 || z < 0 {
            return;
        }

        match self.get_chunk_section_mut(y) {
            Some(s) => {
                if light_type == Light::SKY {
                    s.set_light(light_type, x, y % CHUNK_SECTION_HEIGHT as i16, z, level)
                } else {
                    s.set_light(light_type, x, y % CHUNK_SECTION_HEIGHT as i16, z, level)
                }
            }
            None => return,
        }
    }

    pub fn set_height(&mut self, _height: i16) {
        /*let h = self.height;
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
         */
    }

    pub fn get_all_blocks(&self) -> Vec<u16> {
        // TODO: What the fuck is this
        let blocks: Vec<u16> = self
            .chunk_sections
            .iter()
            .flat_map(|s| s.blocks.iter().cloned()) // TODO: is cloned a good/bad thing
            .collect();

        blocks
    }

    pub fn get_all_data(&self) -> Vec<u8> {
        // TODO: What the fuck is this
        let data: Vec<u8> = self
            .chunk_sections
            .par_iter()
            .flat_map(|s| s.data.par_iter().cloned()) // TODO: is cloned a good/bad thing
            .collect();

        data
    }
}
