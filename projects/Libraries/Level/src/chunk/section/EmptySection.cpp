//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/ImmutableSection.h"
#include "Lodestone.Level/block/instance/BlockInstance.h"
#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"

namespace lodestone::level::chunk::section {
    const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> ImmutableSection::EMPTY_STORAGE = common::storage::palette::PalletizedStorage<block::instance::BlockInstance>(0, *block::instance::ImmutableBlockInstance::getInstance());

    ImmutableSection *ImmutableSection::getInstance() {
        static ImmutableSection s_instance;
        return &s_instance;
    }

    Section::SectionType ImmutableSection::getType() {
        return SectionType::EmptySection;
    }

    const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &ImmutableSection::getStorage() {
        return ImmutableSection::EMPTY_STORAGE;
    }

    lodestone::common::storage::bits::AbstractBitStorage *ImmutableSection::getBlockLight() {
        return common::storage::bits::ImmutableBitStorage::getInstance();
    }

    lodestone::common::storage::bits::AbstractBitStorage *ImmutableSection::getSkyLight() {
        return common::storage::bits::ImmutableBitStorage::getInstance();
    }

    void ImmutableSection::setBlockLight(int x, int y, int z, uint8_t l) {}

    void ImmutableSection::setSkyLight(int x, int y, int z, uint8_t l) {}

    const block::instance::BlockInstance &
    ImmutableSection::getBlock(const int x, const int y, const int z) const {
        return *block::instance::ImmutableBlockInstance::getInstance();
    }

    void ImmutableSection::setBlock(block::instance::BlockInstance &&blk, int x,
                                int y, int z) {}

    uint64_t ImmutableSection::getModificationCount() {
        return 0;
    }
} // namespace lodestone::level::chunk::section
