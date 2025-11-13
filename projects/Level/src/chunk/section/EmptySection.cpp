//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/EmptySection.h"
#include "Lodestone.Level/block/state/BlockState.h"

namespace lodestone::level::chunk::section {
    EmptySection *EmptySection::sInstance = new EmptySection();

    Section::SectionType EmptySection::getType() {
        return SectionType::EmptySection;
    }

    const block::state::BlockState *EmptySection::getBlocks() {
        return nullptr;
    }

    const uint8_t *EmptySection::getBlockLight() const {
        return nullptr;
    }

    const uint8_t *EmptySection::getSkyLight() const {
        return nullptr;
    }

    block::state::BlockState *EmptySection::getBlock(const int x, const int y, const int z) const {
        return new block::state::BlockState();
    }

    void EmptySection::setBlock(block::state::BlockState &&blk, int x, int y, int z) {
    }
}