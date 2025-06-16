use crate::block::{Block, BlockId};
use lodestone_common::util::McVersion;
use crate::block::registry::BLOCK_REGISTRY;

/// Adds a block to the block registry
/// When one wants to convert a block id to the internal id, they will provide an id and a version to the converter method
/// which will get the id for the version closest (downward) to the provided version.
#[macro_export]
macro_rules! add_block_conv {
    (
        // what the fuck
        $reg:expr,
        $blk:expr, [
            $(
                $ver:path : $id:expr
            ),* $(,)?
        ]
    ) => {{
        let mut ids = BTreeMap::new();
        $(
            ids.insert($ver, $id);
        )*
        $reg.blocks.insert($blk, ids);
    }};
}

// TODO: Match Numeric or Flattened with values that are NumericAndFlattened and NumericWithData
pub fn get_internal_block_id(v: McVersion, id: &BlockId) -> Option<Block> {
    for (block, ids) in &BLOCK_REGISTRY.blocks {
        let m = ids.range(..=v).rev().find(|(_, blk_id)| *blk_id == id);

        if m.is_some() {
            return Some(*block);
        }
    }

    None
}

pub fn get_version_block_id(v: McVersion, id: &Block) -> Option<BlockId> {
    BLOCK_REGISTRY.blocks.get(&id).and_then(|ids| {
        ids.range(..=v)
            .rev()
            .next()
            .map(|(_, blk_id)| blk_id.clone())
    })
}
