use crate::block::conversion::{get_internal_block_id, get_version_block_id};
use crate::block::{Block, BlockId};
use crate::level::chunk::{Light, CHUNK_LENGTH, CHUNK_SECTION_HEIGHT, CHUNK_WIDTH};
use lodestone_common::util::McVersion;
use palettevec::{
    index_buffer::aligned::AlignedIndexBuffer, palette::hybrid::HybridPalette, PaletteVec,
};
use std::collections::BTreeMap;

pub type BlockPaletteVec = PaletteVec<Block, HybridPalette<64, Block>, AlignedIndexBuffer>;
pub type StatePaletteVec = PaletteVec<
    BTreeMap<String, String>,
    HybridPalette<64, BTreeMap<String, String>>,
    AlignedIndexBuffer,
>;

#[derive(Clone)]
pub struct ChunkSection {
    // YZX ordering
    // TODO: we could also do palette of block states where we do say 3 bits for block id index and 3 for blockstate index (dynamic)
    pub blocks: BlockPaletteVec,
    pub data: StatePaletteVec,
    pub block_light: Vec<u8>,
    pub sky_light: Vec<u8>,
}

impl ChunkSection {
    pub fn new() -> ChunkSection {
        let blocks = BlockPaletteVec::filled(
            Block::Air,
            CHUNK_WIDTH as usize * CHUNK_SECTION_HEIGHT as usize * CHUNK_LENGTH as usize,
        );
        let data = StatePaletteVec::filled(
            BTreeMap::new(),
            CHUNK_WIDTH as usize * CHUNK_SECTION_HEIGHT as usize * CHUNK_LENGTH as usize,
        );
        ChunkSection {
            blocks,
            data,
            block_light: vec![
                0u8;
                CHUNK_WIDTH as usize
                    * CHUNK_SECTION_HEIGHT as usize
                    * CHUNK_LENGTH as usize
            ],
            sky_light: vec![
                0u8;
                CHUNK_WIDTH as usize
                    * CHUNK_SECTION_HEIGHT as usize
                    * CHUNK_LENGTH as usize
            ],
        }
    }

    #[inline(always)]
    pub fn get_index(x: i8, y: i16, z: i8) -> usize {
        // y as usize + (z as usize * CHUNK_SECTION_HEIGHT as usize) + (x as usize * CHUNK_SECTION_HEIGHT as usize * CHUNK_LENGTH as usize)
        y as usize * 16 * 16 + z as usize * 16 + x as usize
    }

    pub fn get_block(&self, x: i8, y: i16, z: i8) -> Block {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return Block::Air;
        }

        match self.blocks.get(Self::get_index(x, y, z)) {
            Some(block) => *block,
            None => Block::Air,
        }
    }

    pub fn set_block(&mut self, x: i8, y: i16, z: i8, block: Block) {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return;
        }

        self.blocks.set(Self::get_index(x, y, z), &block);
    }

    pub fn get_state(&self, x: i8, y: i16, z: i8) -> Option<&BTreeMap<String, String>> {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return None;
        }

        self.data.get(Self::get_index(x, y, z))
    }

    pub fn set_state(&mut self, x: i8, y: i16, z: i8, key: String, value: String) {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return;
        }

        let mut s = self.data.get(Self::get_index(x, y, z)).unwrap().clone();
        s.insert(key, value);
        self.data.set(Self::get_index(x, y, z), &s);
    }

    pub fn get_light(&self, light_type: Light, x: i8, y: i16, z: i8) -> u8 {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return 0;
        }

        if light_type == Light::SKY {
            self.sky_light[Self::get_index(x, y, z)]
        } else {
            self.block_light[Self::get_index(x, y, z)]
        }
    }

    pub fn set_light(&mut self, light_type: Light, x: i8, y: i16, z: i8, mut level: u8) {
        if x > CHUNK_WIDTH
            || y > CHUNK_SECTION_HEIGHT as i16
            || z > CHUNK_LENGTH
            || x < 0
            || y < 0
            || z < 0
        {
            return;
        }

        // don't let it overflow past max light level
        if level > 15 {
            level = 15;
        }

        let i = Self::get_index(x, y, z);

        if light_type == Light::SKY {
            self.sky_light[i] = level;
        } else {
            self.block_light[i] = level;
        }
    }

    pub fn convert_blocks_to_internal_format(
        version: McVersion,
        arr: Vec<BlockId>,
    ) -> Vec<Option<Block>> {
        arr.iter()
            .map(|v| get_internal_block_id(version, v))
            .collect()
    }

    pub fn convert_blocks_from_internal_format(
        version: McVersion,
        arr: Vec<Block>,
    ) -> Vec<Option<BlockId>> {
        arr.iter()
            .map(|v| get_version_block_id(version, v))
            .collect()
    }
}
