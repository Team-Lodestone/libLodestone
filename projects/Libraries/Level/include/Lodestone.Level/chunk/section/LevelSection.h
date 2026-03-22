//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELSECTION_H
#define LODESTONE_LEVELSECTION_H

#include <Lodestone.Common/Constants.h>

#include <Lodestone.Common/storage/palette/PalletizedStorage.h>
#include "Lodestone.Level/block/instance/BlockInstance.h"
#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"
#include "Lodestone.Level/chunk/section/Section.h"
#include <Lodestone.Common/storage/bits/BitStorage.h>

namespace lodestone::level::chunk::section {
    class LODESTONE_LEVEL_API LevelSection : public Section {
      public:
        LevelSection() = default;
        ~LevelSection() override;

        lodestone::common::storage::bits::AbstractBitStorage *getBlockLight() override;

        lodestone::common::storage::bits::AbstractBitStorage *getSkyLight() override;

        void setBlockLight(int x, int y, int z, uint8_t l) override;

        void setSkyLight(int x, int y, int z, uint8_t l) override;

        const block::instance::BlockInstance &getBlock(int x, int y,
                                                     int z) const override;

        void setBlock(block::instance::BlockInstance &&blk, int x, int y,
                      int z) override;

        const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &getStorage() override;

        SectionType getType() override;

        uint64_t getModificationCount() override;

      private:
        common::storage::palette::PalletizedStorage<block::instance::BlockInstance> m_blocks = common::storage::palette::PalletizedStorage<block::instance::BlockInstance>(common::constants::CHUNK_WIDTH *
                                                                                                                                                                common::constants::SECTION_HEIGHT *
                                                                                                                                                                common::constants::CHUNK_DEPTH, *block::instance::ImmutableBlockInstance::getInstance());
        // TODO: we could also calculate lighting for blocks, could have a map
        // of xyz -> Block specifically for light blocks

        common::storage::bits::BitStorage m_blockLight = common::storage::bits::BitStorage(
            common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT *
                common::constants::CHUNK_DEPTH,
            4);
        common::storage::bits::BitStorage m_skyLight = common::storage::bits::BitStorage(
            common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT *
                common::constants::CHUNK_DEPTH,
            4);
        const char **m_biomes =
            new const char *[common::constants::CHUNK_WIDTH *
                             common::constants::CHUNK_DEPTH]();

        unsigned long m_modificationCount = 0; //how many times the section was modified since it was added, I use this to rebuild the mesh when incremented
        // TODO: should biomes be numeric?
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_LEVELSECTION_H