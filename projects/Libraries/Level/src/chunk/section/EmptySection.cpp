//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/EmptySection.h"
#include "Lodestone.Level/block/properties/BlockProperties.h"
#include "Lodestone.Level/block/properties/EmptyBlockProperties.h"

namespace lodestone::level::chunk::section {
    EmptySection *EmptySection::getInstance() {
        static EmptySection sInstance;
        return &sInstance;
    }

    Section::SectionType EmptySection::getType() {
        return SectionType::EmptySection;
    }

    const block::properties::BlockProperties *EmptySection::getBlocks() {
        return nullptr;
    }

    types::NibbleArray EmptySection::getBlockLight() const {
        return this->mEmptyNibbleArray;
    }

    types::NibbleArray EmptySection::getSkyLight() const {
        return this->mEmptyNibbleArray;
    }

    block::properties::BlockProperties *
    EmptySection::getBlock(const int x, const int y, const int z) const {
        return block::properties::EmptyBlockProperties::getInstance();
    }

    void EmptySection::setBlock(block::properties::BlockProperties &&blk, int x,
                                int y, int z) {}
} // namespace lodestone::level::chunk::section
