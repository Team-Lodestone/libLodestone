//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYSECTION_H
#define LODESTONE_EMPTYSECTION_H

#include "Lodestone.Level/block/properties/BlockProperties.h"
#include "Lodestone.Level/chunk/section/LevelSection.h"
#include "Lodestone.Level/chunk/section/Section.h"
#include "Lodestone.Level/types/EmptyNibbleArray.h"

namespace lodestone::level::chunk::section {
    /** Immutable section, used in place of returning empty/null LevelSection */
    class EmptySection : public Section {
      public:
        static EmptySection *getInstance();

        SectionType getType() override;

        const block::properties::BlockProperties *getBlocks() override;

        types::NibbleArray getBlockLight() const override;

        types::NibbleArray getSkyLight() const override;

        block::properties::BlockProperties *
        getBlock(const int x, const int y, const int z) const override;

        void setBlock(block::properties::BlockProperties &&blk, int x, int y,
                      int z) override;

      private:
        types::EmptyNibbleArray mEmptyNibbleArray = types::EmptyNibbleArray(
            common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT *
                common::constants::CHUNK_DEPTH,
            4);
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_EMPTYSECTION_H