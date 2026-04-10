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
    class LevelSection : public Section {
    public:
        LevelSection() = default;

        ~LevelSection() override;

        SectionType type() override;

        void setBlockLight(int localX, int localY, int localZ, uint8_t lightLevel) override;

        void setSkyLight(int localX, int localY, int localZ, uint8_t lightLevel) override;

        const block::instance::BlockInstance &getBlock(int localX, int localY, int localZ) const override;

        void setBlock(block::instance::BlockInstance &&block, int localX, int localY, int localZ) override;

        lodestone::common::storage::bits::AbstractBitStorage *getBlockLightStorage() override;

        lodestone::common::storage::bits::AbstractBitStorage *getSkyLightStorage() override;

        const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &getBlockStorage() override;

        uint64_t getModificationCount() override;

    private:
        common::storage::palette::PalletizedStorage<block::instance::BlockInstance> m_blockStorage = common::storage::palette::PalletizedStorage<
            block::instance::BlockInstance>(TOTAL_SECTION_3D_SIZE, *block::instance::ImmutableBlockInstance::getInstance());
        // TODO: we could also calculate lighting for blocks, could have a map
        // of xyz -> Block specifically for light blocks

        common::storage::bits::BitStorage m_blockLightStorage = common::storage::bits::BitStorage(TOTAL_SECTION_3D_SIZE, 4);
        common::storage::bits::BitStorage m_skyLightStorage = common::storage::bits::BitStorage(TOTAL_SECTION_3D_SIZE, 4);

        // TODO biome registry
        const char **m_biomes = new const char *[TOTAL_SECTION_2D_SIZE]();

        unsigned long m_modificationCount = 0;
        //how many times the section was modified since it was added, I use this to rebuild the mesh when incremented
        // TODO: should biomes be numeric?
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_LEVELSECTION_H