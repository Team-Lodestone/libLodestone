//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELSECTION_H
#define LODESTONE_LEVELSECTION_H

#include <Lodestone.Common/Constants.h>

#include "Lodestone.Level/block/properties/BlockProperties.h"
#include "Lodestone.Level/chunk/section/Section.h"
#include "Lodestone.Level/types/NibbleArray.h"

namespace lodestone::level::chunk::section {
    class LevelSection : public Section {
      public:
        LevelSection();
        ~LevelSection() override;

        types::AbstractNibbleArray *getBlockLight() override;

        types::AbstractNibbleArray *getSkyLight() override;

        void setBlockLight(int x, int y, int z, uint8_t l) override;

        void setSkyLight(int x, int y, int z, uint8_t l) override;

        block::properties::BlockProperties *getBlock(int x, int y,
                                                     int z) const override;

        void setBlock(block::properties::BlockProperties &&blk, int x, int y,
                      int z) override;

        const block::properties::BlockProperties *getBlocks() override;

        SectionType getType() override;

      private:
        block::properties::BlockProperties *mBlocks = new block::properties::
            BlockProperties[common::constants::CHUNK_WIDTH *
                            common::constants::SECTION_HEIGHT *
                            common::constants::CHUNK_DEPTH]();
        // TODO: we could also calculate lighting for blocks, could have a map
        // of xyz -> Block specifically for light blocks

        types::NibbleArray mBlockLight = types::NibbleArray(
            common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT *
                common::constants::CHUNK_DEPTH,
            4);
        types::NibbleArray mSkyLight = types::NibbleArray(
            common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT *
                common::constants::CHUNK_DEPTH,
            4);
        const char **mBiomes =
            new const char *[common::constants::CHUNK_WIDTH *
                             common::constants::CHUNK_DEPTH]();
        // TODO: should biomes be numeric?
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_LEVELSECTION_H