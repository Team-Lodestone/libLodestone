//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/EmptySection.h"
#include "Lodestone.Level/block/properties/BlockProperties.h"

namespace lodestone::level::chunk::section {
    EmptySection *EmptySection::sInstance = new EmptySection();

    Section::SectionType EmptySection::getType() {
        return SectionType::EmptySection;
    }

    const block::properties::BlockProperties *EmptySection::getBlocks() {
        return nullptr;
    }

    const uint8_t *EmptySection::getBlockLight() const {
        return nullptr;
    }

    const uint8_t *EmptySection::getSkyLight() const {
        return nullptr;
    }

    block::properties::BlockProperties *EmptySection::getBlock(const int x, const int y, const int z) const {
        return new block::properties::BlockProperties();
    }

    void EmptySection::setBlock(block::properties::BlockProperties &&blk, int x, int y, int z) {
    }
}