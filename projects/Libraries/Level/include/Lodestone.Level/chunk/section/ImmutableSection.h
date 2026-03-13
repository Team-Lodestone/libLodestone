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
        static const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> EMPTY_STORAGE;
      public:
        static ImmutableSection *getInstance();

        SectionType getType() override;

        const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &getStorage() override;

        lodestone::common::storage::bits::AbstractBitStorage *getBlockLight() override;

        lodestone::common::storage::bits::AbstractBitStorage *getSkyLight() override;

        void setBlockLight(int x, int y, int z, uint8_t l) override;

        void setSkyLight(int x, int y, int z, uint8_t l) override;

        const block::instance::BlockInstance &
        getBlock(const int x, const int y, const int z) const override;

        void setBlock(block::instance::BlockInstance &&blk, int x, int y,
                      int z) override;

        uint64_t getModificationCount() override;
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_EMPTYSECTION_H