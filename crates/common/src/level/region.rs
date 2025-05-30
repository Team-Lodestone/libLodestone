// use regex::Regex;
use wasm_bindgen::prelude::wasm_bindgen;
// use lodestone_level::level::level::Coords;

#[derive(PartialEq)]
pub enum Compression {
    GZip = 1,
    Zlib = 2,
    None = 3,
    LZ4 = 4,
    Custom = 127 // never will properly support...
}

#[derive(Clone, Default)]
pub struct ChunkLocation {
    pub offset: u32,
    pub size: u8
}

impl TryFrom<i8> for Compression {
    type Error = ();

    fn try_from(c: i8) -> Result<Self, Self::Error> {
        match c {
            r if r == Compression::GZip as i8 => Ok(Compression::GZip),
            r if r == Compression::Zlib as i8 => Ok(Compression::Zlib),
            r if r == Compression::None as i8 => Ok(Compression::None),
            r if r == Compression::LZ4 as i8 => Ok(Compression::LZ4),
            r if r == Compression::Custom as i8 => Ok(Compression::Custom),
            _ => Err(()),
        }
    }
}

// h
// #[wasm_bindgen]
// impl Region {
//     #[wasm_bindgen]
//     pub fn get_min_chunk_coord_x(&self) -> i32 {
//         self.pos.x * 32
//     }
//
//     #[wasm_bindgen]
//     pub fn get_max_chunk_coord_x(&self) -> i32 {
//         self.pos.x * 32 + 32
//     }
//
//     #[wasm_bindgen]
//     pub fn get_min_chunk_coord_z(&self) -> i32 {
//         self.pos.z * 32
//     }
//
//     #[wasm_bindgen]
//     pub fn get_max_chunk_coord_z(&self) -> i32 {
//         self.pos.z * 32 + 32
//     }
//
//     #[wasm_bindgen]
//     pub fn get_coords_from_filename(n: &str) -> Coords {
//         let r = Regex::new(r"r\.([-0-9]{1,2})\.([-0-9]{1,2})\.mcr");
//         if let Some(caps) = r.unwrap().captures(&n) {
//             let x = caps.get(1).unwrap().as_str().parse::<i32>().unwrap();
//             let z = caps.get(2).unwrap().as_str().parse::<i32>().unwrap();
//             Coords { x, z }
//         } else {
//             panic!("Filename does not match MCR name format... (r.(x).(z).mcr)");
//         }
//     }
// }
