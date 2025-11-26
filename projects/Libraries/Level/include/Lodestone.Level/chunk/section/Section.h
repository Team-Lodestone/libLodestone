//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_SECTION_H
#define LODESTONE_SECTION_H
#include "Lodestone.Level/types/NibbleArray.h"

namespace lodestone::level::block {
    namespace properties {
        class BlockProperties;
    }
} // namespace lodestone::level::block

namespace lodestone::level::chunk::section {
    class Section {
      public:
        virtual ~Section() = default;

        enum class SectionType { LevelSection, EmptySection };

        virtual const block::properties::BlockProperties *getBlocks() = 0;

        virtual types::AbstractNibbleArray *getBlockLight() = 0;

        virtual types::AbstractNibbleArray *getSkyLight() = 0;

        virtual void setBlockLight(int x, int y, int z, uint8_t l) = 0;

        virtual void setSkyLight(int x, int y, int z, uint8_t l) = 0;

        virtual block::properties::BlockProperties *
        getBlock(const int x, const int y, const int z) const = 0;

        virtual void setBlock(block::properties::BlockProperties &&blk, int x,
                              int y, int z) = 0;

        virtual SectionType getType() = 0;

        // todo make section have reference to chunk
    };
} // namespace lodestone::level::chunk::section

#endif // LODESTONE_SECTION_H