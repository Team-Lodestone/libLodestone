pub mod conversion;
pub mod registry;
pub mod material;
pub mod internal_blocks;

use lodestone_common::util::McVersion;
use std::collections::{BTreeMap, HashMap};
use crate::block::internal_blocks::Block;

#[derive(Eq, Hash, PartialEq, Clone, Debug)]
pub struct BlockInfo {
    /// Block ID
    pub id: Option<u32>,
    /// Block Variant (e.g 1:3 for 3rd variant)
    pub variant: Option<u8>,
    /// Block ID String
    pub str: Option<String>
}

impl Default for BlockInfo {
    fn default() -> Self {
        BlockInfo {
            id: Some(0),
            variant: Some(0),
            str: Some("minecraft:air".to_string())
        }
    }
}

pub struct BlockRegistry {
    /// List of blocks and every id of that block per version
    pub blocks: HashMap<Block, BTreeMap<McVersion, BlockInfo>>,
    /// List of versions and every block inside each version
    pub versions: BTreeMap<McVersion, HashMap<BlockInfo, Block>>,
}