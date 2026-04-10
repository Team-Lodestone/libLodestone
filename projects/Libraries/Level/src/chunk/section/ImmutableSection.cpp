//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/ImmutableSection.h"
#include "Lodestone.Level/block/instance/BlockInstance.h"
#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"

namespace lodestone::level::chunk::section {
    const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> ImmutableSection::EMPTY_BLOCK_STORAGE = common::storage::palette::PalletizedStorage<block::instance::BlockInstance>(0, *block::instance::ImmutableBlockInstance::getInstance());

    ImmutableSection *ImmutableSection::getInstance() {
        static ImmutableSection s_instance;
        return &s_instance;
    }

    SectionType ImmutableSection::type() {
        return SectionType::ImmutableSection;
    }

    const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &ImmutableSection::getBlockStorage() {
        return ImmutableSection::EMPTY_BLOCK_STORAGE;
    }

    lodestone::common::storage::bits::AbstractBitStorage *ImmutableSection::getBlockLightStorage() {
        return common::storage::bits::ImmutableBitStorage::getInstance();
    }

    lodestone::common::storage::bits::AbstractBitStorage *ImmutableSection::getSkyLightStorage() {
        return common::storage::bits::ImmutableBitStorage::getInstance();
    }

    void ImmutableSection::setBlockLight(int localX, int localY, int localZ, uint8_t lightLevel) {}

    void ImmutableSection::setSkyLight(int localX, int localY, int localZ, uint8_t lightLevel) {}

    const block::instance::BlockInstance &
    ImmutableSection::getBlock(const int localX, const int localY, const int localZ) const {
        return *block::instance::ImmutableBlockInstance::getInstance();
    }

    void ImmutableSection::setBlock(block::instance::BlockInstance &&block, int localX, int localY, int localZ) {}

    uint64_t ImmutableSection::getModificationCount() {
        return 0;
    }
} // namespace lodestone::level::chunk::section
