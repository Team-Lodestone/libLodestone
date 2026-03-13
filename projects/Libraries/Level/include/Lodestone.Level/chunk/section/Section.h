//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_SECTION_H
#define LODESTONE_SECTION_H
#include <Lodestone.Common/storage/palette/PalletizedStorage.h>
#include <Lodestone.Common/storage/bits/BitStorage.h>

namespace lodestone::level::block {
    namespace instance {
        class BlockInstance;
    }
} // namespace lodestone::level::block

namespace lodestone::level::chunk::section {
    class Section {
      public:
        virtual ~Section() = default;

        enum class SectionType { LevelSection, EmptySection };

        virtual const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &getStorage() = 0;

        virtual lodestone::common::storage::bits::AbstractBitStorage *getBlockLight() = 0;

        virtual lodestone::common::storage::bits::AbstractBitStorage *getSkyLight() = 0;

        virtual void setBlockLight(int x, int y, int z, uint8_t l) = 0;

        virtual void setSkyLight(int x, int y, int z, uint8_t l) = 0;

        virtual const block::instance::BlockInstance &
        getBlock(const int x, const int y, const int z) const = 0;

        virtual void setBlock(block::instance::BlockInstance &&blk, int x,
                              int y, int z) = 0;

        virtual SectionType getType() = 0;

        // todo make section have reference to chunk

        virtual uint64_t getModificationCount() = 0;
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_SECTION_H