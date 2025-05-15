pub mod mcgalaxy_lvl;

use wasm_bindgen::prelude::*;

// TODO: central Level class that we can inherit
// well actually idk if this will happen, still trying to figure that out...
#[derive(Debug, Clone)]
#[wasm_bindgen(getter_with_clone)]
pub struct ClassicLevel {
    pub width: i16,
    pub height: i16,
    pub depth: i16,
    pub blocks: Vec<u8>,
}

#[wasm_bindgen]
impl ClassicLevel {
    #[wasm_bindgen]
    pub fn resize(&mut self, width: i16, depth: i16, height: i16) {
        let x0 = self.width as usize;
        let z0 = self.depth as usize;
        let y0 = self.height as usize;

        // hate usize
        let x1 = width as usize;
        let z1 = depth as usize;
        let y1 = height as usize;

        let mut blocks = vec![0; x1 * z1 * y1];
        // can't wait for the order to change between every edition of minecraft
        for x in 0..x0.min(x1) {
            for z in 0..z0.min(z1) {
                for y in 0..y0.min(y1) {
                    let p0 = (y * z0 + z) * x0 + x;
                    let p1 = (y * z1 + z) * x1 + x;
                    blocks[p1] = self.blocks[p0];
                }
            }
        }

        self.blocks = blocks;
        self.width = x1 as i16;
        self.depth = z1 as i16;
        self.height = y1 as i16;
    }
}