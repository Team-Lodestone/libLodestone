use wasm_bindgen::prelude::wasm_bindgen;

#[derive(PartialEq, Clone)]
#[wasm_bindgen(getter_with_clone)]
pub enum Light {
    BLOCK,
    SKY,
}

#[derive(Clone, Debug)]
#[wasm_bindgen(getter_with_clone)]
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

    pub height_map: Vec<i16>,
    pub block_map: Vec<u16>,
}

#[wasm_bindgen(getter_with_clone)]
impl Chunk {
    pub fn new(height: i16) -> Chunk {
        let width: usize = 16;
        let depth: usize = 16;
        let height: usize = height as usize;

        Chunk {
            width: width as i8,
            height: height as i16,
            depth: depth as i8,
            
            blocks: vec![0u16; width * height * depth],
            data: vec![0u8; width * height * depth],
            block_light: vec![0u8; width * depth],
            sky_light: vec![0u8; width * depth],
            
            height_map: vec![0i16; width * depth],
            block_map: vec![0u16; width * depth]
        }
    }
    
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

    pub fn get_index(&self, x: i8, y: i16, z: i8) -> usize {
        (y as usize) + (z as usize) * (self.height as usize) + (x as usize) * (self.height as usize) * 16
    }

    pub fn get_block(&self, x: i8, y: i16, z: i8) -> u16 {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.blocks[self.get_index(x, y, z)]
    }

    pub fn set_block(&mut self, x: i8, y: i16, z: i8, block: u16) {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return;
        }

        let i = self.get_index(x, y, z);

        // println!("{}", self.height);
        self.blocks[i] = block;
    }

    pub fn get_data(&self, x: i8, y: i16, z: i8) -> u8 {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.data[self.get_index(x, y, z)]
    }

    pub fn set_state(&mut self, x: i8, y: i16, z: i8, state: u8) {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return;
        }

        let i = self.get_index(x, y, z);

        self.data[i] = state;
    }

    pub fn get_light(&self, light_type: Light, x: i8, y: i16, z: i8) -> u8 {
        if x > 16 || y > self.height || z > 16 || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        if light_type == Light::SKY {
            self.sky_light[self.get_index(x, y, z)]
        } else {
            self.block_light[self.get_index(x, y, z)]
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

        let i = self.get_index(x, y, z);

        if light_type == Light::SKY {
            self.sky_light[i] = level;
        } else {
            self.block_light[i] = level;
        }
    }

    pub fn set_height(&mut self, height: i16) {
        self.height = height;

        // code we stole from temu
        self.blocks.resize((self.width as usize) * (height as usize) * (self.depth as usize), 0);
    }
}
