use lodestone_common::types::hashmap_ext::Value;
use quartz_nbt::NbtCompound;
use std::collections::HashMap;

pub struct BlockEntity {
    pub id: u16,
    pub x: i32,
    pub y: i32,
    pub z: i32,
    pub components: NbtCompound, // see line 13's comment
    pub keep_packed: bool,       // apparently whether the block entity should NOT be placed

    pub data: HashMap<String, Value>, // TODO: should we store raw nbt in here or actual usable values
}
