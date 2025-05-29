use std::collections::HashMap;
use byteorder::{BigEndian, ReadBytesExt};
use flate2::read::{GzDecoder, ZlibDecoder};
use lodestone_common::level::region::ChunkLocation;
use lodestone_common::level::region::Coords;
use lodestone_common::level::region::{Compression, RegionLike};
use simdnbt::owned::{BaseNbt, Nbt, NbtCompound, NbtList, NbtTag};
use std::io::{Cursor, Read};
use wasm_bindgen::prelude::wasm_bindgen;

#[derive(Clone, Default)]
#[wasm_bindgen(getter_with_clone)]
pub struct Chunk {
    pub coords: Coords,
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
    pub region_like: RegionLike,
    chunks: HashMap<Coords, Chunk>
}

#[wasm_bindgen]
impl Region {

    #[wasm_bindgen]
    pub fn new() -> Region {
        Region {
            chunks: HashMap::new(),
            region_like: RegionLike {
                pos: Coords::default()
            }
        }
    }

    // error: cannot return a borrowed ref with #[wasm_bindgen]
    // how can we fix this?
    #[wasm_bindgen]
    pub fn get_chunk(&self, coords: Coords) -> Option<Chunk> {
        self.chunks.get(&coords).cloned()
    }

    #[wasm_bindgen]
    pub fn new_from_data(data: Vec<u8>, x: i32, z: i32) -> Result<Region, String> {
        let mut c = Cursor::new(data);
        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];
        let mut chunks = HashMap::new();

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
            if (l.size as usize) * 4096 == 0 {
                let coords: Coords = Coords { x: -127, z: -127 };
                chunks.insert(coords.clone(), Chunk::new(coords));
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

            // TODO: support the other 2 methods
            let dec: Option<Box<dyn Read>> = match compression {
                Compression::Zlib => Some(Box::new(ZlibDecoder::new(Cursor::new(compressed.clone())))), // cloning seems really janky...?
                Compression::GZip => Some(Box::new(GzDecoder::new(Cursor::new(compressed.clone())))),
                Compression::None => None,
                _ => { panic!("Unsupported compression format!") } // is this a good idea? I don't know if you can "catch" a panic...
            };

            if compression != Compression::None {
                dec.expect("Decompressor").read_to_end(&mut chunk_data).expect("Decompressed chunk data");
            } else {
                chunk_data = compressed.to_vec();
            }

            let ch = Chunk::new_from_data(chunk_data).expect("Region Chunk from data");
            chunks.insert(ch.clone().coords, ch);
        }

        Ok(Region {
            region_like: RegionLike {
                pos: Coords {
                    x,
                    z
                }
            },
            chunks
        })
    }
}

#[wasm_bindgen]
impl Chunk {
    #[wasm_bindgen]
    pub fn new(coords: Coords) -> Chunk {
        Chunk {
            coords,
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

    pub fn generate_heightmap(&self) -> Vec<u8> {
        let mut heightmap: Vec<u8> = Vec::with_capacity(16*16);

        for z in 0..16 {
            for x in 0..16 {
                for y in (0..128).rev() {
                    let blk = self.get_block(x, y, z);
                    if blk != 0 {
                        heightmap.push((y + 1).min(127) as u8);
                        break;
                    }
                }
            }
        }

        heightmap
    }

    pub fn generate_blockmap(&self) -> Vec<u16> {
        let mut blkmap: Vec<u16> = Vec::with_capacity(16*16);

        for z in 0..16 {
            for x in 0..16 {
                for y in (0..128).rev() {
                    let blk = self.get_block(x, y, z);
                    if !lodestone_common::block::get_block(blk).expect("Get block for blockmap").is_translucent_map {
                        blkmap.push(blk);
                        break;
                    }
                }
            }
        }

        blkmap
    }

    pub fn get_block(&self, x: i16, y: i16, z: i16) -> u16 {
        if x > 16 || y > 128 || z > 16
            || x < 0 || y < 0 || z < 0 {
            return 0;
        }

        self.blocks[(y as usize) + (z as usize) * 128 + (x as usize) * 128 * 16] as u16
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
        
        Ok(Chunk {
            coords: Coords { x, z },
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

// TODO: can't expose to WASM with &mut Vec<u8>
impl Chunk {
    pub fn write(&self, out: &mut Vec<u8>) {
        let c = Nbt::Some(BaseNbt::new(
            "Level",
            NbtCompound::from_values(vec![
                ("xPos".into(), NbtTag::Int(self.coords.x)),
                ("zPos".into(), NbtTag::Int(self.coords.z)),
                ("LastUpdate".into(), NbtTag::Long(self.last_update)),
                ("Blocks".into(), NbtTag::ByteArray(self.blocks.clone())),
                ("Data".into(), NbtTag::ByteArray(self.block_data.clone())),
                ("SkyLight".into(), NbtTag::ByteArray(self.sky_light.clone())),
                ("BlockLight".into(), NbtTag::ByteArray(self.block_light.clone())),
                ("HeightMap".into(), NbtTag::ByteArray(self.height_map.clone())),
                ("LastUpdate".into(), NbtTag::Long(self.last_update)),
                ("Entities".into(), NbtTag::List(self.entities.clone())),
                ("TileEntities".into(), NbtTag::List(self.tile_entities.clone())),
                ("TerrainPopulated".into(), NbtTag::Byte(self.has_populated)),
            ]),
        ));

        c.write(out);
    }
}