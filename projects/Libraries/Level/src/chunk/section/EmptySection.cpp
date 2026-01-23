//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/ImmutableSection.h"
#include "Lodestone.Level/block/properties/BlockProperties.h"
#include "Lodestone.Level/block/properties/ImmutableBlockProperties.h"

namespace lodestone::level::chunk::section {
    const common::storage::palette::PalletizedStorage<block::properties::BlockProperties> ImmutableSection::EMPTY_STORAGE = common::storage::palette::PalletizedStorage<block::properties::BlockProperties>(0, *block::properties::ImmutableBlockProperties::getInstance());

    ImmutableSection *ImmutableSection::getInstance() {
        static ImmutableSection sInstance;
        return &sInstance;
    }

    Section::SectionType ImmutableSection::getType() {
        return SectionType::EmptySection;
    }

    const common::storage::palette::PalletizedStorage<block::properties::BlockProperties> &ImmutableSection::getStorage() {
        return ImmutableSection::EMPTY_STORAGE;
    }

    lodestone::common::storage::bits::AbstractBitsArray *ImmutableSection::getBlockLight() {
        return common::storage::bits::ImmutableBitsArray::getInstance();
    }

    lodestone::common::storage::bits::AbstractBitsArray *ImmutableSection::getSkyLight() {
        return common::storage::bits::ImmutableBitsArray::getInstance();
    }

    void ImmutableSection::setBlockLight(int x, int y, int z, uint8_t l) {}

    void ImmutableSection::setSkyLight(int x, int y, int z, uint8_t l) {}

    const block::properties::BlockProperties &
    ImmutableSection::getBlock(const int x, const int y, const int z) const {
        return *block::properties::ImmutableBlockProperties::getInstance();
    }

    void ImmutableSection::setBlock(block::properties::BlockProperties &&blk, int x,
                                int y, int z) {}
} // namespace lodestone::level::chunk::section
