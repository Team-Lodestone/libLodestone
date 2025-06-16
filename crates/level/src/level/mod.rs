pub mod chunk;
pub mod chunk_section;
pub mod metadata;
pub mod region;

use crate::block::Block;
use crate::level::chunk::{Chunk, Light, CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_common::types::hashmap_ext::Value;
use rayon::iter::IntoParallelRefIterator;
use rayon::iter::ParallelIterator;
use serde::{Deserialize, Serialize};
use std::cmp::min;
use std::collections::{BTreeMap, HashMap};

#[derive(Clone, Default, PartialEq, Eq, Hash, Debug, Serialize, Deserialize)]
pub struct Coords {
    pub x: i32,
    pub z: i32,
}

#[derive(Debug, Clone, Serialize, Deserialize, Copy)]
pub struct Spawn {
    pub x: i32,
    pub y: i32,
    pub z: i32,
}

#[derive(Clone)]
pub struct Level {
    pub name: String,
    pub time: i64,
    pub spawn: Spawn,

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
        for cx in 0..w.div_ceil(CHUNK_WIDTH as i32) {
            for cz in 0..l.div_ceil(CHUNK_LENGTH as i32) {
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
    pub fn get_block(&self, x: i32, y: i16, z: i32) -> Block {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_block(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
            )
        } else {
            Block::Air
        }
    }

    #[inline(always)]
    pub fn set_block(&mut self, x: i32, y: i16, z: i32, block: Block) {
        if let Some(chunk) = self.get_chunk_by_block_coords_mut(x, z) {
            chunk.set_block(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
                block,
            )
        }
    }

    pub fn set_spawn_point(&mut self, x: i32, y: i32, z: i32) {
        self.spawn.x = x;
        self.spawn.y = y;
        self.spawn.z = z;
    }

    pub fn get_chunk_count(&self) -> usize {
        self.chunks.len()
    }

    pub fn set_data(&mut self, x: i32, y: i16, z: i32, key: String, value: String) {
        if let Some(chunk) = self.get_chunk_by_block_coords_mut(x, z) {
            chunk.set_state(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
                key,
                value,
            );
        }
    }

    pub fn get_states(&self, x: i32, y: i16, z: i32) -> Option<&BTreeMap<String, String>> {
        if let Some(chunk) = self.get_chunk_by_block_coords(x, z) {
            chunk.get_state(
                x.rem_euclid(CHUNK_WIDTH as i32) as i8,
                y,
                z.rem_euclid(CHUNK_LENGTH as i32) as i8,
            )
        } else {
            None
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
        self.chunks.iter().map(|c| c.0.x).min().unwrap_or(0)
    }

    pub fn get_min_block_y(&self) -> i16 {
        self.chunks.iter().map(|c| c.1.height).min().unwrap_or(0)
    }

    pub fn get_min_z(&self) -> i32 {
        self.chunks.iter().map(|c| c.0.z).min().unwrap_or(0)
    }

    #[inline(always)]
    pub fn get_max_block_x(&self) -> i32 {
        self.get_max_x() * CHUNK_WIDTH as i32
    }

    #[inline(always)]
    pub fn get_max_block_z(&self) -> i32 {
        self.get_max_z() * CHUNK_LENGTH as i32
    }

    pub fn get_chunk(&self, coords: &Coords) -> Option<&Chunk> {
        self.chunks.get(&coords)
    }

    pub fn get_chunk_mut(&mut self, coords: &Coords) -> Option<&mut Chunk> {
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
    // upd: slightly faster now
    pub fn get_blockmap(&self) -> Vec<Block> {
        let mx = self.get_min_x();
        let mz = self.get_min_z();

        let w = self.get_width() as usize * CHUNK_WIDTH as usize;
        let l = self.get_length() as usize * CHUNK_LENGTH as usize;

        let c: Vec<(Coords, Vec<Block>)> = self
            .chunks
            .par_iter()
            .map(|(p, c)| {
                let mut bm = c.generate_blockmap();
                bm.resize((CHUNK_WIDTH as usize) * (CHUNK_LENGTH as usize), Block::Air);
                (p.clone(), bm)
            })
            .collect();

        let mut blockmap = vec![Block::Air; w * l];

        for (chunk_pos, bm) in c {
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

    pub fn get_heightmap(&self) -> Vec<i16> {
        let mx = self.get_min_x();
        let mz = self.get_min_z();

        let w = self.get_width() as usize * CHUNK_WIDTH as usize;
        let l = self.get_length() as usize * CHUNK_LENGTH as usize;

        let c: Vec<(Coords, Vec<i16>)> = self
            .chunks
            .par_iter()
            .map(|(p, c)| (p.clone(), c.get_heightmap().to_vec()))
            .collect();

        let mut heightmap = vec![-1i16; w * l];

        for (chunk_pos, hm) in c {
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

    pub fn generate_bitmap(&self) -> Vec<u8> {
        let width = self.get_block_width() as usize;
        let length = self.get_block_length() as usize;
        println!("Getting blockmap");
        let block_map = self.get_blockmap();
        println!("Getting heightmap");
        let height_map = self.get_heightmap();

        let mut img = vec![0u8; width * length * 4];

        println!("Writing heightmap");

        // shading written by friend (who does not wish to be named) :)
        for y in 0..length {
            for x in 0..width {
                // TODO: use block map from id to internal block struct which contains Material
                let mut rgb: [f32; 3] = crate::block::palette::CLASSIC_PALETTE
                    [min(50, block_map[x + y * width] as u16) as usize];

                if height_map[x + y * width]
                    < height_map[x + (y as i64 - 1).max(0) as usize * width]
                {
                    rgb[0] *= 0.75;
                    rgb[1] *= 0.75;
                    rgb[2] *= 0.75;
                } else if height_map[x + y * width]
                    > height_map[x + (y as i64 - 1).max(0) as usize * width]
                {
                    rgb[0] *= 1.25;
                    rgb[1] *= 1.25;
                    rgb[2] *= 1.25;
                }

                img[(x + y * width) * 4 + 0] = rgb[0].floor() as u8;
                img[(x + y * width) * 4 + 1] = rgb[1].floor() as u8;
                img[(x + y * width) * 4 + 2] = rgb[2].floor() as u8;
                img[(x + y * width) * 4 + 3] = 0xff;
            }
        }

        img
    }
}
