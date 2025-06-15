use crate::entity::block_entity::BlockEntity;
use lodestone_common::util::McVersion;
use quartz_nbt::NbtCompound;

pub mod alpha;

pub trait BlockEntityHandler {
    fn parse(version: McVersion, nbt: &NbtCompound) -> Option<BlockEntity>;
    fn write(version: McVersion) -> NbtCompound;
}
