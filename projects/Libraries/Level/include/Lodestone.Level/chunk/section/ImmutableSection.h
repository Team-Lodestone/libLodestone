//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYSECTION_H
#define LODESTONE_EMPTYSECTION_H

#include "Lodestone.Level/block/instance/BlockInstance.h"
#include "Lodestone.Level/chunk/section/LevelSection.h"
#include "Lodestone.Level/chunk/section/Section.h"
#include <Lodestone.Common/storage/bits/ImmutableBitStorage.h>

namespace lodestone::level::chunk::section {
    /** Immutable section, used in place of returning empty/null LevelSection */
    class ImmutableSection : public Section {
    private:
        static const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> EMPTY_BLOCK_STORAGE;
      public:
        static ImmutableSection *getInstance();

        SectionType type() override;

        uint64_t getModificationCount() override;

        const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &getBlockStorage() override;

        const block::instance::BlockInstance &getBlock(const int localX, const int localY, const int localZ) const override;
        void setBlock(block::instance::BlockInstance &&block, int localX, int localY, int localZ) override;

        lodestone::common::storage::bits::AbstractBitStorage *getBlockLightStorage() override;
        lodestone::common::storage::bits::AbstractBitStorage *getSkyLightStorage() override;

        void setBlockLight(int localX, int localY, int localZ, uint8_t lightLevel) override;
        void setSkyLight(int localX, int localY, int localZ, uint8_t lightLevel) override;
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_EMPTYSECTION_H