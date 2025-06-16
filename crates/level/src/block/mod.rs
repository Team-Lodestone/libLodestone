pub mod palette;
pub mod conversion;

use std::collections::{BTreeMap, HashMap};
use phf::phf_map;
use lodestone_common::util::McVersion;
use once_cell::sync::Lazy;
use crate::add_block_conv;
use crate::block::BlockId::Numeric;
// pub struct Block {
//     pub name: &'static str,
//     pub string_id: &'static str,
//     pub id: u16,
//     pub is_translucent: bool,
//     pub is_translucent_map: bool,
// }
//
// // closest thing I could come up with
// // this is internal registry that is not tied to any one edition of the game, but can be resolved via id conversion between the editions
// // we will need to have Variant registry though... so this current registry may change quite a lot.
// pub static BLOCKS: phf::Map<u16, Block> = phf_map! {
//     0u16 => Block { id: 0, string_id: "air", name: "Air", is_translucent: true, is_translucent_map: true },
//     1u16 => Block { id: 1, string_id: "stone", name: "Stone", is_translucent: false, is_translucent_map: false },
//     2u16 => Block { id: 2, string_id: "grass_block", name: "Grass Block", is_translucent: false, is_translucent_map: false },
//     3u16 => Block { id: 3, string_id: "dirt", name: "Dirt", is_translucent: false, is_translucent_map: false },
//     4u16 => Block { id: 4, string_id: "cobblestone", name: "Cobblestone", is_translucent: false, is_translucent_map: false },
//     5u16 => Block { id: 5, string_id: "planks", name: "Planks", is_translucent: false, is_translucent_map: false }, // split up into different block per variant post 1.13
//     6u16 => Block { id: 6, string_id: "sapling", name: "Sapling", is_translucent: true, is_translucent_map: true },
//     7u16 => Block { id: 7, string_id: "bedrock", name: "Bedrock", is_translucent: false, is_translucent_map: false }, // I think the game considers them translucent for multiple things
//     8u16 => Block { id: 8, string_id: "flowing_water", name: "Flowing Water", is_translucent: false, is_translucent_map: false },
//     9u16 => Block { id: 9, string_id: "water", name: "Water", is_translucent: false, is_translucent_map: false },
//     10u16 => Block { id: 10, string_id: "flowing_lava", name: "Flowing Lava", is_translucent: false, is_translucent_map: false },
//     11u16 => Block { id: 11, string_id: "lava", name: "Lava", is_translucent: false, is_translucent_map: false },
//     12u16 => Block { id: 12, string_id: "sand", name: "Sand", is_translucent: false, is_translucent_map: false },
//     13u16 => Block { id: 13, string_id: "gravel", name: "Gravel", is_translucent: false, is_translucent_map: false },
//     14u16 => Block { id: 14, string_id: "gold_ore", name: "Gold Ore", is_translucent: false, is_translucent_map: false },
//     15u16 => Block { id: 15, string_id: "iron_ore", name: "Iron Ore", is_translucent: false, is_translucent_map: false },
//     16u16 => Block { id: 16, string_id: "coal_ore", name: "Coal Ore", is_translucent: false, is_translucent_map: false },
//     17u16 => Block { id: 17, string_id: "wood", name: "Wood", is_translucent: false, is_translucent_map: false },
//     18u16 => Block { id: 18, string_id: "leaves", name: "Leaves", is_translucent: true, is_translucent_map: false },
//     19u16 => Block { id: 19, string_id: "sponge", name: "Sponge", is_translucent: false, is_translucent_map: false },
//     20u16 => Block { id: 20, string_id: "glass", name: "Glass", is_translucent: true, is_translucent_map: true },
//     255u16 => Block { id: 255, string_id: "unknown", name: "Unknown", is_translucent: false, is_translucent_map: false }
//     // gonna stop here because I would need to figure out variants as for Classic, all wools were seperated (and I think they were combined later on?)
//     // we could also just do 1.13 strat and make every variant it's own unique block, would be easier in the long run
// };

// pub fn get_block(id: u16) -> Option<&'static Block> {
//     BLOCKS.get(&id).or(BLOCKS.get(&255))
// }

#[derive(Debug)]
enum BlockId {
    Numeric(u16),
    Flattened(String),
    NumericWithData(u16, u16),
    NumericAndFlattened(u16, String),
}


pub struct BlockRegistry {
    blocks: HashMap<Block, BTreeMap<McVersion, BlockId>>,
}

pub static BLOCK_REGISTRY: Lazy<BlockRegistry> = Lazy::new(|| {
    let mut reg = BlockRegistry {
        blocks: HashMap::new(),
    };
    
    add_block_conv!(reg, Block::Stone, [
        McVersion::PreClassic132211: Numeric(1u16),
    ]);
    
    reg
});

/// Internal Block IDs
#[repr(u16)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
enum Block {
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
    UltramarineWool = 29,
    PurpleWool = 30,
    VioletWool = 31,
    MagentaWool = 32,
    PinkWool = 33,
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
    Obsidian = 49
}