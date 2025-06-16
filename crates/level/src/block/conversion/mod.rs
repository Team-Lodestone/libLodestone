mod classic;

use lodestone_common::util::McVersion;
use crate::block::{Block, BlockId};
use crate::block::BlockId::{Flattened, Numeric};
use crate::block::conversion::classic::CLASSIC_BLOCKS;

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

// TODO: we need to be able to exclude certain blocks if they don't exist in the version that we're converting to
// theoretically we could add a MinVersion field to each thing in the map but idk if that would be a good idea.
// I just really don't want to make a map for every single version that added/removed a block
// the bigger issue is how we will convert back into these block ids from our internal ones, is there some way to reverse the map?
fn get_internal_block_id(v: McVersion, id: BlockId) -> Block {
    todo!()
}