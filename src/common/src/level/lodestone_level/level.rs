use crate::level::lodestone_level::chunk::{Chunk, Light};
use crate::level::region::Coords;
use std::collections::HashMap;

pub struct Level {
    pub name: String,
    pub time: i64,

    chunks: HashMap<Coords, Chunk>,
}

impl Level {
    pub fn new(name: String) -> Level {
        Level {
            name,
            time: 0,
            chunks: HashMap::new(),
        }
    }

    pub fn get_chunk(&mut self, coords: Coords) -> Option<&mut Chunk> {
        self.chunks.get_mut(&coords)
    }

    pub fn get_chunk_by_block_coords(&mut self, x: i32, z: i32) -> Option<&mut Chunk> {
        let coords = Coords { x, z };
        self.chunks.get_mut(&coords)
    }

    pub fn add_chunk(&mut self, coords: Coords, chunk: Chunk) {
        self.chunks.insert(coords, chunk);
    }

    pub fn remove_chunk(&mut self, coords: Coords) {
        self.chunks.remove(&coords);
    }

    pub fn get_block(&mut self, x: i32, y: i16, z: i32) -> u16 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_block((x % 16) as i8, y, (z % 16) as i8)
        } else {
            0
        }
    }

    pub fn set_data(&mut self, x: i32, y: i16, z: i32, block: u8) {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.set_state((x % 16) as i8, y, (z % 16) as i8, block);
        }
    }

    pub fn get_data(&mut self, x: i32, y: i16, z: i32) -> u8 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_data((x % 16) as i8, y, (z % 16) as i8)
        } else {
            0
        }
    }

    pub fn set_state(&mut self, x: i32, y: i16, z: i32, state: u8) {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.set_state((x % 16) as i8, y, (z % 16) as i8, state);
        }
    }

    pub fn get_light(&mut self, light_type: Light, x: i32, y: i16, z: i32) -> u8 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_light(light_type, (x % 16) as i8, y, (z % 16) as i8)
        } else {
            0
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i32, y: i16, z: i32, level: u8) {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.set_light(light_type, (x % 16) as i8, y, (z % 16) as i8, level);
        }
    }
}
