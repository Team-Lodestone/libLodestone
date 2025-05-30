// use std::collections::HashMap;
// use byteorder::{BigEndian, ReadBytesExt};
// use flate2::read::{GzDecoder, ZlibDecoder};
// use lodestone_common::level::region::ChunkLocation;
// use lodestone_common::level::region::Coords;
// use lodestone_common::level::region::{Compression, RegionLike};
// use simdnbt::owned::{BaseNbt, Nbt, NbtCompound, NbtList, NbtTag};
// use std::io::{Cursor, Read};
// use wasm_bindgen::prelude::wasm_bindgen;
// use lodestone_level::level::chunk::Chunk;
//
// #[derive(Clone, Default)]
// #[wasm_bindgen(getter_with_clone)]
// pub struct MCRChunk {
//     pub chunk: Chunk,
//     pub last_update: i64,
//     pub has_populated: i8,
// }
//
// #[wasm_bindgen(getter_with_clone)]
// pub struct Region {}
//
// #[wasm_bindgen]
// impl Region {
//
//     #[wasm_bindgen]
//     pub fn new_from_data(data: Vec<u8>, x: i32, z: i32) -> Result<Level, String> {
//         let mut c = Cursor::new(data);
//         let mut locations = vec![ChunkLocation::default(); 1024];
//         let mut timestamps = vec![0i32; 1024];
//         let mut chunks = HashMap::new();
//
//         for l in locations.iter_mut() {
//             let offset = c.read_u24::<BigEndian>().expect("Offset in location");
//             let size = c.read_u8().expect("Size in location");
//
//             *l = ChunkLocation {
//                 offset,
//                 size
//             };
//         }
//
//         for ts in timestamps.iter_mut() {
//             *ts = c.read_i32::<BigEndian>().expect("Chunk timestamp");
//         }
//
//         for l in locations.iter() {
//             if (l.size as usize) * 4096 == 0 {
//                 let coords: Coords = Coords { x: -127, z: -127 };
//                 chunks.insert(coords.clone(), MCRChunk::new());
//                 continue;
//             }
//
//             c.set_position((l.offset as u64) * 4096);
//
//             let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
//             let comp = c.read_i8().expect("Chunk compression");
//             let compression = Compression::try_from(comp).expect("Chunk compression enum");
//
//             let mut compressed = vec![0u8; (len - 1) as usize];
//             // wtf is this slice stuff
//             c.read_exact(compressed.as_mut_slice()).expect("Compressed chunk data");
//
//             let mut chunk_data: Vec<u8> = Vec::new();
//
//             // TODO: support the other 2 methods
//             let dec: Option<Box<dyn Read>> = match compression {
//                 Compression::Zlib => Some(Box::new(ZlibDecoder::new(Cursor::new(compressed.clone())))), // cloning seems really janky...?
//                 Compression::GZip => Some(Box::new(GzDecoder::new(Cursor::new(compressed.clone())))),
//                 Compression::None => None,
//                 _ => { panic!("Unsupported compression format!") } // is this a good idea? I don't know if you can "catch" a panic...
//             };
//
//             // if compression != Compression::None {
//                 dec.expect("Decompressor").read_to_end(&mut chunk_data).expect("Decompressed chunk data");
//             } else {
//                 chunk_data = compressed.to_vec();
//             }
//
//             let ch = MCRChunk::new_from_data(chunk_data).expect("Region Chunk from data");
//             chunks.insert(ch.clone().coords, ch);
//         }
//
//         Ok(Region {
//             region_like: RegionLike {
//                 pos: Coords {
//                     x,
//                     z
//                 }
//             },
//             chunks
//         })
//     }
// }
//
// #[wasm_bindgen]
// impl MCRChunk {
//     #[wasm_bindgen]
//     pub fn new() -> MCRChunk {
//         MCRChunk {
//             Chunk::new(128),
//             last_update: 0,
//             blocks: vec![0u8; 16*256*16],
//             block_data: vec![0u8; 16*256*16],
//             sky_light: vec![0u8; 16*256*16],
//             block_light: vec![0u8; 16*256*16],
//             has_populated: 0,
//             height_map: vec![0u8; 16*256*16],
//             entities: NbtList::default(),
//             tile_entities: NbtList::default()
//         }
//     }
//
//     #[wasm_bindgen]
//     pub fn new_from_data(data: Vec<u8>) -> Result<MCRChunk, String> {
//         let nbt = simdnbt::borrow::read(&mut Cursor::new(&data)).expect("Chunk NBT data").unwrap();
//
//         let level = nbt.compound("Level").expect("Level compound tag");
//
//         let x = level.int("xPos").expect("Chunk x position");
//         let z = level.int("zPos").expect("Chunk z position");
//         let last_update = level.long("LastUpdate").expect("Chunk last modified");
//         let blocks = level.byte_array("Blocks").expect("Chunk blocks").to_vec();
//         let block_data = level.byte_array("Data").expect("Chunk block data").to_vec();
//         let sky_light = level.byte_array("SkyLight").expect("Chunk sky light").to_vec();
//         let block_light = level.byte_array("BlockLight").expect("Chunk block light").to_vec();
//         let height_map = level.byte_array("HeightMap").expect("Chunk heightmap").to_vec();
//         let entities = level.list("Entities").expect("Chunk entities").to_owned();
//         let tile_entities = level.list("TileEntities").expect("Chunk tile entities").to_owned();
//         let has_populated = level.byte("TerrainPopulated").expect("Chunk has populated");
//
//         Ok(MCRChunk {
//             coords: Coords { x, z },
//             last_update,
//             blocks,
//             block_data,
//             sky_light,
//             block_light,
//             height_map,
//             entities,
//             tile_entities,
//             has_populated
//         })
//     }
// }
//
// // TODO: can't expose to WASM with &mut Vec<u8>
// impl MCRChunk {
//     pub fn write(&self, out: &mut Vec<u8>) {
//         let c = Nbt::Some(BaseNbt::new(
//             "Level",
//             NbtCompound::from_values(vec![
//                 ("xPos".into(), NbtTag::Int(self.chunk.coords.x)),
//                 ("zPos".into(), NbtTag::Int(self.chunk.coords.z)),
//                 ("LastUpdate".into(), NbtTag::Long(self.last_update)),
//                 ("Blocks".into(), NbtTag::ByteArray(self.chunk.blocks.clone())),
//                 ("Data".into(), NbtTag::ByteArray(self.chunk.data.clone())),
//                 ("SkyLight".into(), NbtTag::ByteArray(self.chunk.sky_light.clone())),
//                 ("BlockLight".into(), NbtTag::ByteArray(self.chunk.block_light.clone())),
//                 ("HeightMap".into(), NbtTag::ByteArray(self.chunk.height_map.clone())),
//                 ("LastUpdate".into(), NbtTag::Long(self.last_update)),
//                 ("Entities".into(), NbtTag::List()),
//                 ("TileEntities".into(), NbtTag::List()),
//                 ("TerrainPopulated".into(), NbtTag::Byte(self.has_populated)),
//             ]),
//         ));
//
//         c.write(out);
//     }
// }