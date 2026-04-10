//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_SECTION_H
#define LODESTONE_SECTION_H
#include <Lodestone.Common/Constants.h>
#include <Lodestone.Common/util/IHasDerivedTypes.h>

#include <Lodestone.Common/storage/palette/PalletizedStorage.h>
#include <Lodestone.Common/storage/bits/BitStorage.h>

namespace lodestone::level::block {
    namespace instance {
        class BlockInstance;
    }
} // namespace lodestone::level::block

namespace lodestone::level::chunk::section {
    enum class SectionType { LevelSection, ImmutableSection };

    class Section : public common::util::IHasDerivedTypes<SectionType> {
      public:
        static constexpr int TOTAL_SECTION_3D_SIZE = common::constants::CHUNK_WIDTH * common::constants::SECTION_HEIGHT * common::constants::CHUNK_DEPTH;
        static constexpr int TOTAL_SECTION_2D_SIZE = common::constants::CHUNK_WIDTH * common::constants::CHUNK_DEPTH;

        virtual const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &getBlockStorage() = 0;

        virtual common::storage::bits::AbstractBitStorage *getBlockLightStorage() = 0;

        virtual common::storage::bits::AbstractBitStorage *getSkyLightStorage() = 0;

        virtual void setBlockLight(int localX, int localY, int localZ, uint8_t lightLevel) = 0;

        virtual void setSkyLight(int localX, int localY, int localZ, uint8_t lightLevel) = 0;

        virtual const block::instance::BlockInstance &
        getBlock(const int localX, const int localY, const int localZ) const = 0;

        virtual void setBlock(block::instance::BlockInstance &&block, int localX,
                              int localY, int localZ) = 0;

        // todo make section have reference to chunk

        virtual uint64_t getModificationCount() = 0;
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_SECTION_H