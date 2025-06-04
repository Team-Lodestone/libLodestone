pub mod chunk;
pub mod metadata;

use crate::level::chunk::{Chunk, Light, CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_common::types::hashmap_ext::Value;
use serde::{Deserialize, Serialize};
use serde_with::serde_as;
use std::collections::HashMap;

#[derive(Clone, Default, PartialEq, Eq, Hash, Debug, Serialize, Deserialize)]
pub struct Coords {
    pub x: i32,
    pub z: i32,
}

#[derive(Debug, Clone, Serialize, Deserialize, Copy)]
pub struct Spawn {
    pub x: i16,
    pub y: i16,
    pub z: i16,
}

#[serde_as]
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Level {
    pub name: String,
    pub time: i64,
    pub spawn: Spawn,

    #[serde_as(as = "Vec<(_, _)>")]
    chunks: HashMap<Coords, Chunk>,

    pub custom_data: HashMap<String, Value>,
}

impl Level {
    pub fn new_with_name(name: String) -> Level {
        Level {
            name,
            time: 0,
            chunks: HashMap::new(),
            spawn: Spawn { x: 0, y: 0, z: 0 },
            custom_data: Default::default(),
        }
    }

    pub fn create_finite(&mut self, w: i32, h: i16, l: i32) {
        for cx in 0..(w.div_ceil(CHUNK_WIDTH as i32)) {
            for cz in 0..(l.div_ceil(CHUNK_LENGTH as i32)) {
                // log::debug!("cx: {}, cz: {}", cx, cz);

                let coords = Coords { x: cx, z: cz };
                let chunk = Chunk::new(h);

                self.add_chunk(coords.clone(), chunk);
            }
        }
    }
    pub fn new() -> Level {
        Level {
            name: "New World".to_string(),
            time: 0,
            chunks: HashMap::new(),
            spawn: Spawn { x: 0, y: 0, z: 0 },
            custom_data: Default::default(),
        }
    }

    pub fn add_chunk(&mut self, coords: Coords, chunk: Chunk) {
        if self.chunks.contains_key(&coords) {
            return;
        }

        self.chunks.insert(coords, chunk);
    }

    pub fn remove_chunk(&mut self, coords: Coords) {
        self.chunks.remove(&coords);
    }

    #[inline(always)]
    pub fn get_block(&self, x: i32, y: i16, z: i32) -> u16 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_block(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
            )
        } else {
            0
        }
    }

    #[inline(always)]
    pub fn set_block(&mut self, x: i32, y: i16, z: i32, block: u16) {
        if let Some(chunk) = self.get_chunk_by_block_coords_mut(x, z) {
            chunk.set_block(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
                block,
            )
        }
    }

    pub fn set_spawn_point(&mut self, x: i16, y: i16, z: i16) {
        self.spawn.x = x;
        self.spawn.y = y;
        self.spawn.z = z;
    }

    pub fn get_chunk_count(&self) -> usize {
        self.chunks.len()
    }

    pub fn set_data(&mut self, x: i32, y: i16, z: i32, block: u8) {
        if let Some(chunk) = self.get_chunk_by_block_coords_mut(x, z) {
            chunk.set_state(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8 as i8,
                block,
            );
        }
    }

    pub fn get_data(&self, x: i32, y: i16, z: i32) -> u8 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_data(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8 as i8,
            )
        } else {
            0
        }
    }

    pub fn set_state(&mut self, x: i32, y: i16, z: i32, state: u8) {
        if let Some(chunk) = self.get_chunk_by_block_coords_mut(x, z) {
            chunk.set_state(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
                state,
            );
        }
    }

    pub fn get_light(&self, light_type: Light, x: i32, y: i16, z: i32) -> u8 {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_light(
                light_type,
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
            )
        } else {
            0
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i32, y: i16, z: i32, level: u8) {
        if let Some(chunk) = self.get_chunk_by_block_coords_mut(x, z) {
            chunk.set_light(
                light_type,
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
                level,
            );
        }
    }

    pub fn get_max_x(&self) -> i32 {
        self.chunks.iter().map(|c| (c.0.x) + 1).max().unwrap_or(0)
    }

    pub fn get_max_block_y(&self) -> i16 {
        self.chunks.iter().map(|c| c.1.height).max().unwrap_or(0)
    }

    pub fn get_max_z(&self) -> i32 {
        self.chunks.iter().map(|c| (c.0.z) + 1).max().unwrap_or(0)
    }

    #[inline(always)]
    pub fn get_min_block_x(&self) -> i32 {
        self.get_min_x() * CHUNK_WIDTH as i32
    }

    #[inline(always)]
    pub fn get_min_block_z(&self) -> i32 {
        self.get_min_z() * CHUNK_LENGTH as i32
    }

    pub fn get_min_x(&self) -> i32 {
        self.chunks.iter().map(|c| (c.0.x)).min().unwrap_or(0)
    }

    pub fn get_min_block_y(&self) -> i16 {
        self.chunks.iter().map(|c| c.1.height).min().unwrap_or(0)
    }

    pub fn get_min_z(&self) -> i32 {
        self.chunks.iter().map(|c| (c.0.z)).min().unwrap_or(0)
    }

    #[inline(always)]
    pub fn get_max_block_x(&self) -> i32 {
        self.get_max_x() * CHUNK_WIDTH as i32
    }

    #[inline(always)]
    pub fn get_max_block_z(&self) -> i32 {
        self.get_max_z() * CHUNK_LENGTH as i32
    }

    pub fn get_chunk(&mut self, coords: Coords) -> Option<&mut Chunk> {
        self.chunks.get_mut(&coords)
    }

    pub fn get_chunk_by_block_coords(&self, x: i32, z: i32) -> Option<&Chunk> {
        let coords = Coords {
            x: x.div_euclid(CHUNK_WIDTH as i32),
            z: z.div_euclid(CHUNK_LENGTH as i32),
        };

        self.chunks.get(&coords)
    }

    pub fn get_chunk_by_block_coords_mut(&mut self, x: i32, z: i32) -> Option<&mut Chunk> {
        let coords = Coords {
            x: x.div_euclid(CHUNK_WIDTH as i32),
            z: z.div_euclid(CHUNK_LENGTH as i32),
        };

        self.chunks.get_mut(&coords)
    }

    pub fn get_chunks(&self) -> &HashMap<Coords, Chunk> {
        &self.chunks
    }

    pub fn get_chunks_mut(&mut self) -> &mut HashMap<Coords, Chunk> {
        &mut self.chunks
    }

    // TODO: this works... but is very slow.
    pub fn get_blockmap(&mut self) -> Vec<u16> {
        let mx = self.get_min_x();
        let mz = self.get_min_z();

        let w = self.get_width() as usize * CHUNK_WIDTH as usize;
        let l = self.get_length() as usize * CHUNK_LENGTH as usize;

        let mut blockmap = vec![65535u16; w * l];

        for (chunk_pos, chunk) in self.chunks.iter_mut() {
            let mut bm = chunk.generate_blockmap();
            bm.resize((CHUNK_WIDTH as usize) * (CHUNK_LENGTH as usize), 65535);

            for x in 0..CHUNK_WIDTH as usize {
                for z in 0..CHUNK_LENGTH as usize {
                    let gx = (chunk_pos.x - mx) as usize * CHUNK_WIDTH as usize + x;
                    let gz = (chunk_pos.z - mz) as usize * CHUNK_LENGTH as usize + z;

                    let bi = gz * w + gx;
                    let ci = z * CHUNK_WIDTH as usize + x;

                    blockmap[bi] = bm[ci];
                }
            }
        }

        blockmap
    }

    pub fn get_heightmap(&mut self) -> Vec<i16> {
        let mx = self.get_min_x();
        let mz = self.get_min_z();

        let w = self.get_width() as usize * CHUNK_WIDTH as usize;
        let l = self.get_length() as usize * CHUNK_LENGTH as usize;

        let mut heightmap = vec![-1i16; w * l];

        for (chunk_pos, chunk) in self.chunks.iter_mut() {
            let mut hm = chunk.generate_heightmap();
            hm.resize((CHUNK_WIDTH as usize) * (CHUNK_LENGTH as usize), -1);

            for x in 0..CHUNK_WIDTH as usize {
                for z in 0..CHUNK_LENGTH as usize {
                    let gx = (chunk_pos.x - mx) as usize * CHUNK_WIDTH as usize + x;
                    let gz = (chunk_pos.z - mz) as usize * CHUNK_LENGTH as usize + z;

                    let bi = gz * w + gx;
                    let ci = z * CHUNK_WIDTH as usize + x;

                    heightmap[bi] = hm[ci];
                }
            }
        }

        heightmap
    }

    #[inline(always)]
    pub fn get_width(&self) -> i32 {
        self.get_max_x() - self.get_min_x()
    }

    #[inline(always)]
    pub fn get_block_height(&self) -> i16 {
        self.get_max_block_y()
    }

    #[inline(always)]
    pub fn get_length(&self) -> i32 {
        self.get_max_z() - self.get_min_z()
    }

    #[inline(always)]
    pub fn get_block_width(&self) -> i32 {
        self.get_width() * CHUNK_WIDTH as i32
    }

    #[inline(always)]
    pub fn get_block_length(&self) -> i32 {
        self.get_length() * CHUNK_LENGTH as i32
    }
}
