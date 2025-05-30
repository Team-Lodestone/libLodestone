use crate::level::chunk::{Chunk, Light};
use std::collections::HashMap;
use wasm_bindgen::prelude::wasm_bindgen;

// ffs need this bc can't do tuple with wasm toolchain
#[derive(Clone, Default, PartialEq, Eq, Hash, Debug)]
#[wasm_bindgen(getter_with_clone)]
pub struct Coords {
    pub x: i32,
    pub z: i32,
}

#[derive(Clone, Debug)]
#[wasm_bindgen(getter_with_clone)]
pub struct Level {
    pub name: String,
    pub time: i64,

    chunks: HashMap<Coords, Chunk>
}

#[wasm_bindgen()]
impl Level {
    pub fn new_with_name(name: String) -> Level {
        Level {
            name,
            time: 0,
            chunks: HashMap::new(),
        }
    }

    pub fn new() -> Level {
        Level {
            name: "New World".to_string(),
            time: 0,
            chunks: HashMap::new(),
        }
    }

    pub fn add_chunk(&mut self, coords: Coords, chunk: Chunk) {
        if self.chunks.contains_key(&coords) { return; }

        self.chunks.insert(coords, chunk);
    }

    pub fn remove_chunk(&mut self, coords: Coords) {
        self.chunks.remove(&coords);
    }

    pub fn get_block(&mut self, x: i32, y: i16, z: i32) -> u16 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_block((x % 16) as i8, y, (z % 16) as i8)
        } else {
            18
        }
    }

    pub fn set_block(&mut self, x: i32, y: i16, z: i32, block: u16) {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.set_block((x % 16) as i8, y, (z % 16) as i8, block)
        }
    }

    pub fn get_chunk_count(&self) -> usize {
        self.chunks.len()
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

    pub fn get_width(&self) -> i32  {
        self.chunks.iter().map(|c | (c.0.x) + 1)
            .max()
            .unwrap_or(0)
    }

    pub fn get_block_height(&self) -> i16 {
        self.chunks.iter().map(|c | c.1.height)
            .max()
            .unwrap_or(0)
    }

    pub fn get_depth(&self) -> i32  {
        self.chunks.iter().map(|c | (c.0.z) + 1)
            .max()
            .unwrap_or(0)
    }

    pub fn get_block_width(&self) -> i32  {
        self.get_width() * 16
    }

    pub fn get_block_depth(&self) -> i32  {
        self.get_depth() * 16
    }
}

impl Level {
    pub fn get_chunk(&mut self, coords: Coords) -> Option<&mut Chunk> {
        self.chunks.get_mut(&coords)
    }

    pub fn get_chunk_by_block_coords(&mut self, x: i32, z: i32) -> Option<&mut Chunk> {
        let coords = Coords { x: x / 16, z: z / 16 };

        self.chunks.get_mut(&coords)
    }

    pub fn get_chunks(&self) -> HashMap<Coords, Chunk> {
        self.chunks.clone()
    }
}
