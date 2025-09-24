// This file is auto-generated from block_mappings.json
use strum::IntoEnumIterator;
use crate::block::{BTreeMap, BlockInfo};
use std::collections::HashMap;
use once_cell::sync::Lazy;
use lodestone_common::util::McVersion;
use crate::add_block_conv;
use crate::block::{Block, BlockRegistry};

pub static BLOCK_REGISTRY: Lazy<BlockRegistry> = Lazy::new(|| {
    let mut reg = BlockRegistry {
        blocks: HashMap::new(),
        versions: BTreeMap::new(),
    };
add_block_conv!(reg, Block::Air, [
     McVersion::PreClassic132211: BlockInfo { id: Some(0), variant: None, str: None },
]);
add_block_conv!(reg, Block::Stone, [
     McVersion::PreClassic132211: BlockInfo { id: Some(1), variant: None, str: None },
]);
add_block_conv!(reg, Block::Granite, [
     McVersion::Snapshot14w02a: BlockInfo { id: Some(1), variant: Some(1), str: None },
]);
add_block_conv!(reg, Block::Grass, [
     McVersion::PreClassic132211: BlockInfo { id: Some(2), variant: None, str: None },
]);
add_block_conv!(reg, Block::Dirt, [
     McVersion::PreClassic20090515: BlockInfo { id: Some(3), variant: None, str: None },
]);
add_block_conv!(reg, Block::Cobblestone, [
     McVersion::PreClassic20090515: BlockInfo { id: Some(4), variant: None, str: None },
]);
add_block_conv!(reg, Block::OakPlanks, [
     McVersion::PreClassic20090515: BlockInfo { id: Some(5), variant: None, str: None },
     McVersion::Release1_2_4: BlockInfo { id: Some(5), variant: Some(0), str: None },
]);
add_block_conv!(reg, Block::OakSapling, [
     McVersion::PreClassic161348: BlockInfo { id: Some(6), variant: None, str: None },
     McVersion::Release1_5: BlockInfo { id: Some(6), variant: Some(0), str: None },
]);
add_block_conv!(reg, Block::Bedrock, [
     McVersion::Classic0_0_12a: BlockInfo { id: Some(7), variant: None, str: None },
]);
add_block_conv!(reg, Block::FlowingWater, [
     McVersion::Classic0_0_12a: BlockInfo { id: Some(8), variant: None, str: None },
]);
for (block, ids) in &reg.blocks {
    for (&version, id) in ids {
        for v in McVersion::iter().filter(|v| *v >= version) {
            reg.versions
                .entry(v)
                .or_default()
                .entry(id.clone())
                .or_insert(*block);
        }
    }
}
reg
});
