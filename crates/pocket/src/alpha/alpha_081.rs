use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use lodestone_common::util::McVersion;
use lodestone_level::block::conversion::get_internal_block_id;
use lodestone_level::block::BlockId;
use lodestone_level::level::chunk::Chunk;
use lodestone_level::level::region::ChunkLocation;
use lodestone_level::level::{Coords, Level};
use std::io::{Cursor, Read, Seek, SeekFrom, Write};

pub trait Alpha081Level {
    fn read_alpha081(version: McVersion, data: Vec<u8>) -> Result<Level, String>;
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8>;
}

pub trait Alpha081Chunk {
    fn read_alpha081(version: McVersion, data: Vec<u8>) -> Result<(Chunk, Coords), String>;
    fn write_alpha081(&mut self, version: McVersion, coords: &Coords) -> Vec<u8>;
}

impl Alpha081Level for Level {
    fn read_alpha081(version: McVersion, data: Vec<u8>) -> Result<Level, String> {
        let mut c = Cursor::new(data);
        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut level = Level::new();

        for l in locations.iter_mut() {
            let size = c.read_u8().expect("Size in location");
            let offset = c.read_u24::<LittleEndian>().expect("Offset in location");
            
            *l = ChunkLocation { offset, size };
        }

        Ok(level);
    }
    fn write_alpha081(&mut self, version: McVersion) -> Vec<u8> {

    }
}

impl Alpha081Chunk for Chunk {
    fn read_alpha081(version: McVersion, data: Vec<u8) -> Result<(Chunk, Coords), String> {

    }
    fn write_alpha081(&mut self, version: McVersion, coords: &Coords) -> Vec<u8> {

    }
}