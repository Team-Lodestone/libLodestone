//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELSECTION_H
#define LODESTONE_LEVELSECTION_H

#include <Lodestone.Common/Constants.h>
#include "Lodestone.Level/chunk/section/Section.h"
#include "Lodestone.Level/block/state/BlockState.h"

namespace lodestone::level::chunk::section {
    class LevelSection : public Section {
    public:
        ~LevelSection() override;

        const uint8_t *getBlockLight() const override;

        const uint8_t *getSkyLight() const override;

        block::state::BlockState *getBlock(int x, int y, int z) const override;

        void setBlock(block::state::BlockState &&blk, int x, int y, int z) override;

        const block::state::BlockState *getBlocks() override;

        SectionType getType() override;

    private:
        block::state::BlockState *mBlocks = new block::state::BlockState[
            common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT * common::constants::CHUNK_DEPTH]{};
        // TODO: we could also calculate lighting for blocks, could have a map of xyz -> Block specifically for light blocks

        uint8_t *mBlockLight = new uint8_t[(common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT * common::constants::CHUNK_DEPTH)
                                           / 2]{};
        uint8_t *mSkyLight = new uint8_t[(common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT * common::constants::CHUNK_DEPTH) /
                                         2]{};
        const char **mBiomes = new const char *[common::constants::CHUNK_WIDTH * common::constants::CHUNK_DEPTH]{};
        // TODO: should biomes be numeric?
    };
}

#endif //LODESTONE_LEVELSECTION_H