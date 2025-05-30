pub mod mcgalaxy_lvl;
pub mod mine_v2;

use wasm_bindgen::prelude::*;

// TODO: central Level class that we can inherit
// well actually idk if this will happen, still trying to figure that out...
#[derive(Debug, Clone)]
#[wasm_bindgen(getter_with_clone)]
pub struct ClassicLevel {
    pub width: i16,
    pub height: i16,
    pub length: i16,
    pub blocks: Vec<u8>, // TODO: think about restricting access to the block array and instead provide helpers to access and manipulate it.
}

#[wasm_bindgen]
impl ClassicLevel {
    #[wasm_bindgen]
    pub fn resize(&mut self, width: i16, depth: i16, height: i16) {
        // old size
        let x0 = self.width as usize;
        let z0 = self.length as usize;
        let y0 = self.height as usize;

        // hate usize
        // new size
        let x1 = width as usize;
        let z1 = depth as usize;
        let y1 = height as usize;

        let mut blocks = vec![0; y1 * z1 * x1 ];
        // can't wait for the order to change between every edition of minecraft
        for y in 0..y0.min(y1) {
            for z in 0..z0.min(z1) {
                for x in 0..x0.min(x1) {
                    let p0 = y * z0 * x0 + z * x0 + x; // old
                    let p1 = y * z1 * x1 + z * x1 + x; // new
                    blocks[p1] = self.blocks[p0];
                }
            }
        }

        self.blocks = blocks;
        self.width = x1 as i16;
        self.length = z1 as i16;
        self.height = y1 as i16;
    }

    pub fn get_byte_size(&self) -> usize {
        2 + 2 + 2 + ((self.width as usize) * (self.length as usize) * (self.height as usize))
    }

    #[wasm_bindgen]
    pub fn get_block(&self, x: i16, y: i16, z: i16) -> u8 {
        let index = self.get_index(x, y, z);
        if index == !0 {
            return 0;
        }

        self.blocks[index]
    }

    #[wasm_bindgen]
    pub fn set_block(&mut self, x: i16, y: i16, z: i16, block: u8) {
        let index = self.get_index(x, y, z);
        if index == !0 {
            return;
        }

        self.blocks[index] = block;
    }

    #[wasm_bindgen]
    pub fn get_index(&self, x: i16, y: i16, z: i16) -> usize {
        // our coords
        let x = x as usize;
        let y = y as usize;
        let z = z as usize;

        // world size
        let w = self.width as usize;
        let h = self.height as usize;
        let d = self.length as usize;

        if x < 0 || y < 0 || z < 0 ||
            x >= w || y >= h || z >= d {
            return !0;
        }

        y * (d * w) + z * w + x
    }
}