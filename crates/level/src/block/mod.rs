pub mod conversion;
pub mod palette;

use crate::add_block_conv;
use crate::block::BlockId::{Numeric, NumericAndFlattened};
use lodestone_common::util::McVersion;
use once_cell::sync::Lazy;
use std::collections::{BTreeMap, HashMap};

#[derive(Debug, Eq, PartialEq, Clone)]
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

pub struct BlockRegistry {
    pub blocks: HashMap<Block, BTreeMap<McVersion, BlockId>>,
}

pub static BLOCK_REGISTRY: Lazy<BlockRegistry> = Lazy::new(|| {
    let mut reg = BlockRegistry {
        blocks: HashMap::new(),
    };

    // TODO: rock is stored using same id as air, do we want to change ID?
    add_block_conv!(reg, Block::Air, [
        McVersion::PreClassic20090515: Numeric(0u16),
        McVersion::Release1_13: NumericAndFlattened(0u16, "minecraft:air")
    ]);

    add_block_conv!(reg, Block::Stone, [
        McVersion::PreClassic132211: Numeric(0u16),
        McVersion::PreClassic20090515: Numeric(1u16),
        McVersion::Release1_13: NumericAndFlattened(1u16, "minecraft:stone")
    ]);

    add_block_conv!(reg, Block::Grass, [
        McVersion::PreClassic20090515: Numeric(2u16),
        McVersion::Release1_13: NumericAndFlattened(2u16, "minecraft:grass_block")
    ]);

    add_block_conv!(reg, Block::Dirt, [
        McVersion::PreClassic20090515: Numeric(3u16),
        McVersion::Release1_13: NumericAndFlattened(3u16, "minecraft:dirt")
    ]);

    add_block_conv!(reg, Block::Cobblestone, [
        McVersion::PreClassic20090515: Numeric(4u16),
        McVersion::Release1_13: NumericAndFlattened(4u16, "minecraft:cobblestone")
    ]);

    add_block_conv!(reg, Block::OakPlanks, [
        McVersion::PreClassic20090515: Numeric(5u16),
    ]);

    add_block_conv!(reg, Block::OakSapling, [
       McVersion::PreClassic161348: Numeric(6u16),
    ]);

    add_block_conv!(reg, Block::Bedrock, [
       McVersion::Classic0_0_12a: Numeric(7u16),
    ]);

    add_block_conv!(reg, Block::FlowingWater, [
        McVersion::Classic0_0_12a: Numeric(8u16),
    ]);

    add_block_conv!(reg, Block::Water, [
        McVersion::Classic0_0_12a: Numeric(9u16),
    ]);

    add_block_conv!(reg, Block::FlowingLava, [
        McVersion::Classic0_0_12a: Numeric(10u16),
    ]);

    add_block_conv!(reg, Block::Lava, [
        McVersion::Classic0_0_12a: Numeric(11u16),
    ]);

    add_block_conv!(reg, Block::Sand, [
        McVersion::Classic0_0_14a: Numeric(12u16),
    ]);

    add_block_conv!(reg, Block::Gravel, [
        McVersion::Classic0_0_14a: Numeric(13u16),
    ]);

    add_block_conv!(reg, Block::GoldOre, [
       McVersion::Classic0_0_14a: Numeric(14u16),
    ]);

    add_block_conv!(reg, Block::IronOre, [
        McVersion::Classic0_0_14a: Numeric(15u16),
    ]);

    add_block_conv!(reg, Block::CoalOre, [
        McVersion::Classic0_0_14a: Numeric(16u16),
    ]);

    add_block_conv!(reg, Block::OakLog, [
        McVersion::Classic0_0_14a: Numeric(17u16),
    ]);

    add_block_conv!(reg, Block::OakLeaves, [
        McVersion::Classic0_0_14a: Numeric(18u16),
    ]);

    add_block_conv!(reg, Block::Sponge, [
        McVersion::Classic0_0_19a: Numeric(19u16),
    ]);

    add_block_conv!(reg, Block::Glass, [
        McVersion::Classic0_0_19a: Numeric(20u16),
    ]);

    add_block_conv!(reg, Block::RedWool, [
        McVersion::Classic0_0_20a: Numeric(21u16)
    ]);

    add_block_conv!(reg, Block::OrangeWool, [
        McVersion::Classic0_0_20a: Numeric(22u16),
    ]);

    add_block_conv!(reg, Block::YellowWool, [
        McVersion::Classic0_0_20a: Numeric(23u16),
    ]);

    add_block_conv!(reg, Block::LimeWool, [
        McVersion::Classic0_0_20a: Numeric(24u16),
    ]);

    add_block_conv!(reg, Block::GreenWool, [
        McVersion::Classic0_0_20a: Numeric(25u16),
    ]);

    add_block_conv!(reg, Block::SpringGreenWool, [
        McVersion::Classic0_0_20a: Numeric(26u16),
    ]);

    // Cyan in Classic
    add_block_conv!(reg, Block::LightBlueWool, [
        McVersion::Classic0_0_20a: Numeric(27u16),
    ]);

    // Capri in Classic
    add_block_conv!(reg, Block::CyanWool, [
        McVersion::Classic0_0_20a: Numeric(28u16),
    ]);

    add_block_conv!(reg, Block::BlueWool, [
        McVersion::Classic0_0_20a: Numeric(29u16),
    ]);

    add_block_conv!(reg, Block::VioletWool, [
        McVersion::Classic0_0_20a: Numeric(30u16),
    ]);

    add_block_conv!(reg, Block::PurpleWool, [
        McVersion::Classic0_0_20a: Numeric(31u16),
    ]);

    add_block_conv!(reg, Block::MagentaWool, [
        McVersion::Classic0_0_20a: Numeric(32u16),
    ]);

    add_block_conv!(reg, Block::PinkWool, [
        McVersion::Classic0_0_20a: Numeric(33u16),
    ]);

    add_block_conv!(reg, Block::DarkGrayWool, [
        McVersion::Classic0_0_20a: Numeric(34u16),
    ]);

    add_block_conv!(reg, Block::GrayWool, [
        McVersion::Classic0_0_20a: Numeric(35u16),
    ]);

    add_block_conv!(reg, Block::WhiteWool, [
        McVersion::Classic0_0_20a: Numeric(36u16),
    ]);

    add_block_conv!(reg, Block::Dandelion, [
        McVersion::Classic0_0_20a: Numeric(37u16),
    ]);

    add_block_conv!(reg, Block::RedMushroom, [
        McVersion::Classic0_0_20a: Numeric(38u16),
    ]);

    add_block_conv!(reg, Block::Rose, [
        McVersion::Classic0_0_20a: Numeric(39u16),
    ]);

    add_block_conv!(reg, Block::BrownMushroom, [
        McVersion::Classic0_0_20a: Numeric(40u16),
    ]);

    add_block_conv!(reg, Block::RedMushroom, [
        McVersion::Classic0_0_20a: Numeric(41u16),
    ]);

    add_block_conv!(reg, Block::GoldBlock, [
        McVersion::Classic0_0_20a: Numeric(42u16),
    ]);

    reg
});

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
