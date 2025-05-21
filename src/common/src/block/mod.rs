use phf::phf_map;

pub struct Block {
    pub name: &'static str,
    pub string_id: &'static str,
    pub id: u8,
    pub is_translucent: bool,
    pub is_translucent_map: bool
}

// closest thing I could come up with
// this is internal registry that is not tied to any one edition of the game, but can be resolved via id conversion between the editions
// we will need to have Variant registry though... so this current registry may change quite a lot.
pub static BLOCKS: phf::Map<u8, Block> = phf_map! {
    0u8 => Block { id: 0, string_id: "air", name: "Air", is_translucent: true, is_translucent_map: true },
    1u8 => Block { id: 1, string_id: "stone", name: "Stone", is_translucent: false, is_translucent_map: false },
    2u8 => Block { id: 2, string_id: "grass_block", name: "Grass Block", is_translucent: false, is_translucent_map: false },
    3u8 => Block { id: 3, string_id: "dirt", name: "Dirt", is_translucent: false, is_translucent_map: false },
    4u8 => Block { id: 4, string_id: "cobblestone", name: "Cobblestone", is_translucent: false, is_translucent_map: false },
    5u8 => Block { id: 5, string_id: "planks", name: "Planks", is_translucent: false, is_translucent_map: false }, // split up into different block per variant post 1.13
    6u8 => Block { id: 6, string_id: "sapling", name: "Sapling", is_translucent: true, is_translucent_map: true },
    7u8 => Block { id: 7, string_id: "bedrock", name: "Bedrock", is_translucent: false, is_translucent_map: false }, // I think the game considers them translucent for multiple things
    8u8 => Block { id: 8, string_id: "flowing_water", name: "Flowing Water", is_translucent: false, is_translucent_map: false },
    9u8 => Block { id: 9, string_id: "water", name: "Water", is_translucent: false, is_translucent_map: false },
    10u8 => Block { id: 10, string_id: "flowing_lava", name: "Flowing Lava", is_translucent: false, is_translucent_map: false },
    11u8 => Block { id: 11, string_id: "lava", name: "Lava", is_translucent: false, is_translucent_map: false },
    12u8 => Block { id: 12, string_id: "sand", name: "Sand", is_translucent: false, is_translucent_map: false },
    13u8 => Block { id: 13, string_id: "gravel", name: "Gravel", is_translucent: false, is_translucent_map: false },
    14u8 => Block { id: 14, string_id: "gold_ore", name: "Gold Ore", is_translucent: false, is_translucent_map: false },
    15u8 => Block { id: 15, string_id: "iron_ore", name: "Iron Ore", is_translucent: false, is_translucent_map: false },
    16u8 => Block { id: 16, string_id: "coal_ore", name: "Coal Ore", is_translucent: false, is_translucent_map: false },
    17u8 => Block { id: 17, string_id: "wood", name: "Wood", is_translucent: false, is_translucent_map: false },
    18u8 => Block { id: 18, string_id: "leaves", name: "Leaves", is_translucent: true, is_translucent_map: false },
    19u8 => Block { id: 19, string_id: "sponge", name: "Sponge", is_translucent: false, is_translucent_map: false },
    20u8 => Block { id: 20, string_id: "glass", name: "Glass", is_translucent: true, is_translucent_map: true },
    255u8 => Block { id: 255, string_id: "unknown", name: "Unknown", is_translucent: false, is_translucent_map: false }
    // gonna stop here because I would need to figure out variants as for Classic, all wools were seperated (and I think they were combined later on?)
    // we could also just do 1.13 strat and make every variant it's own unique block, would be easier in the long run
};

pub fn get_block(id: u8) -> Option<&'static Block> {
    BLOCKS.get(&id).or(BLOCKS.get(&255))
}