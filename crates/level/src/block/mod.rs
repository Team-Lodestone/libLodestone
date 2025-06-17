pub mod conversion;
pub mod palette;
pub mod registry;

use crate::add_block_conv;
use crate::block::BlockId::{Flattened, Numeric, NumericAndFlattened, NumericWithData};
use lodestone_common::util::McVersion;
use once_cell::sync::Lazy;
use std::collections::{BTreeMap, HashMap};

#[derive(Debug, Eq, PartialEq, Clone)]
#[derive(Hash)]
pub enum BlockId {
    /// Numeric id only
    Numeric(u16),
    /// Block ID string only
    Flattened(&'static str),
    /// Numeric ID but the block also has data for its block state (e.g 1:6 for Polished Andesite)
    NumericWithData(u16, u16),
    /// Numeric ID paired with a flattened block ID string
    NumericAndFlattened(u16, &'static str),
}

impl Default for BlockId {
    fn default() -> Self {
        BlockId::NumericAndFlattened(0, "minecraft:air")
    }
}

impl TryFrom<BlockId> for usize {
    type Error = &'static str;

    fn try_from(v: BlockId) -> Result<Self, Self::Error> {
        match v {
            Numeric(b) => Ok(b as usize),
            NumericWithData(b, _) => Ok(b as usize),
            NumericAndFlattened(b, _) => Ok(b as usize),
            Flattened(_) => Err("Can't convert flattened block id to number"),
        }
    }
}


pub struct BlockRegistry {
    /// List of blocks and every id of that block per version
    pub blocks: HashMap<Block, BTreeMap<McVersion, BlockId>>,
    /// List of versions and every block inside each version
    pub versions: HashMap<McVersion, HashMap<BlockId, Block>>,
}

/// Internal Block IDs
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u16)]
pub enum Block {
    Air = 0,
    Stone = 1,
    Grass = 2,
    Dirt = 3,
    Cobblestone = 4,
    OakPlanks = 5,
    OakSapling = 6,
    Bedrock = 7,
    FlowingWater = 8,
    Water = 9,
    FlowingLava = 10,
    Lava = 11,
    Sand = 12,
    Gravel = 13,
    GoldOre = 14,
    IronOre = 15,
    CoalOre = 16,
    OakLog = 17,
    OakLeaves = 18,
    Sponge = 19,
    Glass = 20,
    // WOOL
    RedWool = 21,
    OrangeWool = 22,
    YellowWool = 23,
    LimeWool = 24, // Chartreuse (fairly close to lime so can be considered the same during conversion)
    GreenWool = 25, // In Classic, it's a light green, but in later versions, it's a dark green.
    SpringGreenWool = 26, // Only exists in Classic
    LightBlueWool = 27, // in Classic it's called Cyan Cloth
    CyanWool = 28, // in Classic it's called Capri Cloth
    BlueWool = 29, // in Classic it's called Ultramarine Cloth
    PurpleWool = 30,
    VioletWool = 31,
    MagentaWool = 32,
    PinkWool = 33, // in Classic it's called Rose Cloth
    DarkGrayWool = 34,
    GrayWool = 35,
    WhiteWool = 36, // Base wool block in modern
    Dandelion = 37,
    Rose = 38,
    BrownMushroom = 39,
    RedMushroom = 40,
    GoldBlock = 41,
    IronBlock = 42,
    DoubleSmoothStoneSlab = 43,
    SmoothStoneSlab = 44,
    Bricks = 45,
    Tnt = 46,
    Bookshelf = 47,
    MossyCobblestone = 48,
    Obsidian = 49,
}
