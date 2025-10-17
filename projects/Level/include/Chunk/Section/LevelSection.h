//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELSECTION_H
#define LODESTONE_LEVELSECTION_H

#include "Constants.h"
#include "Indexing.h"
#include "Section.h"
#include "Block/State/BlockState.h"

namespace lodestone::level::chunk::section {
    class LevelSection : public Section {
    public:
        const uint8_t *getBlockLight() const override;
        const uint8_t *getSkyLight() const override;

        block::state::BlockState *getBlock(int x, int y, int z) const override;
        void setBlock(block::state::BlockState &blk, int x, int y, int z) override;

        const block::state::BlockState *getBlocks() override;

        SectionType getType() override;
    private:
        block::state::BlockState *mBlocks = new block::state::BlockState[constants::CHUNK_WIDTH * constants::SECTION_HEIGHT * constants::CHUNK_LENGTH];

        uint8_t *mBlockLight = new uint8_t[constants::CHUNK_WIDTH * constants::SECTION_HEIGHT * constants::CHUNK_LENGTH];
        uint8_t *mSkyLight = new uint8_t[constants::CHUNK_WIDTH * constants::SECTION_HEIGHT * constants::CHUNK_LENGTH];
    };
}

#endif //LODESTONE_LEVELSECTION_H
