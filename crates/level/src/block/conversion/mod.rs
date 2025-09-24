use crate::block::{Block, BlockInfo};
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

#[inline(always)]
pub fn get_internal_block_id(v: McVersion, id: &BlockInfo) -> Option<Block> {
    BLOCK_REGISTRY
        .versions
        .range(..=v)
        .rev()
        .find_map(|(_ver, blocks)| blocks.get(id).copied())
}

#[inline(always)]
pub fn get_version_block_id(v: McVersion, id: &Block) -> BlockInfo {
    BLOCK_REGISTRY
        .blocks
        .get(id)
        .and_then(|ids| {
            ids.range(..=v)
                .rev()
                .next()
                .map(|(_, blk_id)| blk_id.clone())
        })
        .unwrap_or(BlockInfo::default())
}

#[inline(always)]
pub fn convert_blocks_to_internal_format(
    version: McVersion,
    arr: Vec<BlockInfo>,
) -> Vec<Option<Block>> {
    arr.iter()
        .map(|v| get_internal_block_id(version, v))
        .collect()
}

#[inline(always)]
pub fn convert_blocks_from_internal_format(
    version: McVersion,
    arr: Vec<Block>,
) -> Vec<BlockInfo> {
    arr.iter()
        .map(|v| get_version_block_id(version, v))
        .collect()
}
