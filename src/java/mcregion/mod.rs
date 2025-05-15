use std::io::{Cursor, Read};
use byteorder::{BigEndian, ReadBytesExt};
use flate2::read::{GzDecoder, ZlibDecoder};
use flate2::write::GzEncoder;
use simdnbt::borrow::NbtCompoundList;
use simdnbt::owned::{NbtCompound, NbtList};
use wasm_bindgen::prelude::wasm_bindgen;

#[derive(Clone, Default)]
#[wasm_bindgen(getter_with_clone)]
pub struct ChunkLocation {
    offset: u32,
    size: u8
}

#[derive(Clone, Default)]
#[wasm_bindgen(getter_with_clone)]
pub struct Chunk {
    pub x: i32,
    pub z: i32,
    pub last_update: i64,
    pub blocks: Vec<u8>,
    pub block_data: Vec<u8>,
    pub sky_light: Vec<u8>,
    pub block_light: Vec<u8>,
    pub has_populated: i8,
    pub height_map: Vec<u8>,
    entities: NbtList, // TODO: make public once we make WASM thing for it
    tile_entities: NbtList // TODO: make public once we make WASM thing for it
}

#[wasm_bindgen(getter_with_clone)]
pub struct Region {
    x: i32,
    z: i32,
    chunks: Vec<Chunk>
}

#[wasm_bindgen(getter_with_clone)]
pub enum Compression {
    GZip = 1,
    Zlib = 2,
    None = 3,
    LZ4 = 4,
    Custom = 127 // never will properly support...
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

#[wasm_bindgen]
impl Region {
    #[wasm_bindgen]
    pub fn get_min_chunk_coord_x(&self) -> i32 {
        self.x * 32
    }

    #[wasm_bindgen]
    pub fn get_max_chunk_coord_x(&self) -> i32 {
        self.x * 32 + 31
    }

    #[wasm_bindgen]
    pub fn get_min_chunk_coord_z(&self) -> i32 {
        self.z * 32
    }

    #[wasm_bindgen]
    pub fn get_max_chunk_coord_z(&self) -> i32 {
        self.z * 32 + 31
    }

    #[wasm_bindgen]
    pub fn new() -> Region {
        Region {
            chunks: Vec::with_capacity(1024),
            x: 0,
            z: 0
        }
    }

    // error: cannot return a borrowed ref with #[wasm_bindgen]
    // how can we fix this?
    // also, we need to find a better way to get coords... this is slow.
    #[wasm_bindgen]
    pub fn get_chunk(&self, x: i32, z: i32) -> Option<Chunk> {
        for chunk in &self.chunks {
            if chunk.x == x && chunk.z == z {
                return Some(chunk.clone());
            }
        }
        None
    }

    #[wasm_bindgen]
    pub fn new_from_data(data: Vec<u8>, x: i32, z: i32) -> Result<Region, String> {
        let mut c = Cursor::new(data);
        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];
        let mut chunks = Vec::with_capacity(1024);

        for l in locations.iter_mut() {
            let offset = c.read_u24::<BigEndian>().expect("Offset in location");
            let size = c.read_u8().expect("Size in location");

            *l = ChunkLocation {
                offset,
                size
            };
        }

        for ts in timestamps.iter_mut() {
            *ts = c.read_i32::<BigEndian>().expect("Chunk timestamp");
        }

        for l in locations.iter() {
            if ((l.size as usize) * 4096 == 0) {
                chunks.push(Chunk::new(-127, -127));
                continue;
            }

            c.set_position((l.offset as u64) * 4096);

            let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
            let comp = c.read_i8().expect("Chunk compression");
            let compression = Compression::try_from(comp).expect("Chunk compression enum");

            let mut compressed = vec![0u8; (len - 1) as usize];
            // wtf is this slice stuff
            c.read_exact(compressed.as_mut_slice()).expect("Compressed chunk data");

            let mut chunk_data: Vec<u8> = Vec::new();

            // TODO: support the other methods
            let mut dec = ZlibDecoder::new(Cursor::new(compressed));
            dec.read_to_end(&mut chunk_data).expect("Decompressed chunk data");

            let ch = Chunk::new_from_data(chunk_data).expect("Region Chunk from data");
            chunks.push(ch);
        }

        Ok(Region {
            x,
            z,
            chunks
        })
    }
}

#[wasm_bindgen]
impl Chunk {
    #[wasm_bindgen]
    pub fn new(x: i32, z: i32) -> Chunk {
        Chunk {
            x,
            z,
            last_update: 0,
            blocks: vec![0u8; 16*256*16],
            block_data: vec![0u8; 16*256*16],
            sky_light: vec![0u8; 16*256*16],
            block_light: vec![0u8; 16*256*16],
            has_populated: 0,
            height_map: vec![0u8; 16*256*16],
            entities: NbtList::default(),
            tile_entities: NbtList::default()
        }
    }

    #[wasm_bindgen]
    pub fn new_from_data(data: Vec<u8>) -> Result<Chunk, String> {
        let nbt = simdnbt::borrow::read(&mut Cursor::new(&data)).expect("Chunk NBT data").unwrap();

        let level = nbt.compound("Level").expect("Level compound tag");

        let x = level.int("xPos").expect("Chunk x position");
        let z = level.int("zPos").expect("Chunk z position");
        let last_update = level.long("LastUpdate").expect("Chunk last modified");
        let blocks = level.byte_array("Blocks").expect("Chunk blocks").to_vec();
        let block_data = level.byte_array("Data").expect("Chunk block data").to_vec();
        let sky_light = level.byte_array("SkyLight").expect("Chunk sky light").to_vec();
        let block_light = level.byte_array("BlockLight").expect("Chunk block light").to_vec();
        let height_map = level.byte_array("HeightMap").expect("Chunk heightmap").to_vec();
        let entities = level.list("Entities").expect("Chunk entities").to_owned();
        let tile_entities = level.list("TileEntities").expect("Chunk tile entities").to_owned();
        let has_populated = level.byte("TerrainPopulated").expect("Chunk has populated");

        println!("x: {}, z: {}", x, z);

        Ok(Chunk {
            x,
            z,
            last_update,
            blocks,
            block_data,
            sky_light,
            block_light,
            height_map,
            entities,
            tile_entities,
            has_populated
        })
    }
}