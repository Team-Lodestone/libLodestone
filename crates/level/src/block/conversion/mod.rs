mod classic;

use crate::block::conversion::classic::CLASSIC_BLOCKS;
use crate::block::Block;
use lodestone_common::util::McVersion;

// TODO: we need to be able to exclude certain blocks if they don't exist in the version that we're converting to
// theoretically we could add a MinVersion field to each thing in the map but idk if that would be a good idea.
// I just really don't want to make a map for every single version that added/removed a block
// the bigger issue is how we will convert back into these block ids from our internal ones, is there some way to reverse the map?
fn get_internal_block_id(v: McVersion, id: usize) -> Block {
    match v {
        McVersion::Classic030 => CLASSIC_BLOCKS
            .get(&(id as u8))
            .copied()
            .unwrap_or(Block::Air),
        McVersion::Alpha1_2_6 => todo!(),
    }
}
