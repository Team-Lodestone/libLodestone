use crate::entity::parsing::alpha::AlphaBlockEntityParser;
use crate::entity::parsing::BlockEntityHandler;
use lodestone_common::util::McVersion;
use quartz_nbt::NbtCompound;

// Guidelines:
// Should contain everything the modern Tile Entity has
// if it doesn't, then converted tile entities will be missing data.
// We can put this in any format we like, as long as it can be converted back, then it's fine.
#[derive(Clone)]
pub enum BlockEntityType {
    Furnace {
        items: Vec<Item>,
        lit_time_remaining: i16,
        cooking_time_spent: i16,
        cooking_total_time: i16,
        lit_total_time: i16,
        lockable_container: LockableContainer,
        recipes_used: RecipesUsed,
    },
    Chest {
        items: Vec<Item>, // TODO: apparently there's an Item component, FUCK
        lockable_container: LockableContainer,
        loot_table: LootTable,
    },
    JukeBox {
        record: i32,
    },
    Dispenser {
        items: Vec<Item>,
    },
    Sign {
        waxed: bool,
        text: Vec<String>, // TODO: Text components and other shit
    },
    MobSpawner {
        entity_id: String,
        delay: i16,
    },
    Music {
        note: i8,
    },
    Piston {
        block_id: i32,
        block_data: i32,
        facing: i32,
        progress: f32,
        extending: bool,
    },
}

#[derive(Clone)]
pub enum HasBlockEntity {
    Found(BlockEntityType),
    NotFound(String, NbtCompound),
}

#[derive(Clone)]
pub struct LootTable {
    pub name: String,
    pub seed: i64,
}

#[derive(Clone)]
pub struct LockableContainer {
    pub lock: bool,
}

#[derive(Clone)]
pub struct RecipesUsed {
    pub id: u16,
}

#[derive(Clone)]
pub struct Item {
    pub slot: u8,
    pub id: u16,
    pub count: i32,
}

#[derive(Clone)]
pub struct BlockEntity {
    pub id: String,
    pub x: i32,
    pub y: i32,
    pub z: i32,
    pub components: NbtCompound, // what the fuck do we do with this? I just say store it raw for now until we properly parse it.
    pub keep_packed: bool,       // apparently whether the block entity should NOT be placed

    pub data: HasBlockEntity, // TODO: should we store raw nbt in here or actual usable values
}

impl BlockEntity {
    pub fn from_nbt(version: McVersion, nbt: &NbtCompound) -> Option<BlockEntity> {
        // todo: match closest version DOWN from version given if version given does not have an entry
        // entries in here should only be when a new format was implemented.
        match version {
            // TODO: get first version that implemented alpha block entities
            McVersion::Alpha1_2_6 => AlphaBlockEntityParser::parse(version, nbt),
            _ => None,
        }
    }
}
