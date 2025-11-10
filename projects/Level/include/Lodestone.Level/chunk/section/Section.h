//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_SECTION_H
#define LODESTONE_SECTION_H
#include <cstdint>

namespace lodestone::level::block {
    namespace state {
        class BlockState;
    }
}

namespace lodestone::level::chunk::section {
    class Section {
    public:
        virtual ~Section() = default;

        enum class SectionType {
            LevelSection,
            EmptySection
        };

        virtual const block::state::BlockState *getBlocks() = 0;

        virtual const uint8_t *getBlockLight() const = 0;

        virtual const uint8_t *getSkyLight() const = 0;

        virtual block::state::BlockState *getBlock(const int x, const int y, const int z) const = 0;

        virtual void setBlock(block::state::BlockState &blk, int x, int y, int z) = 0;

        virtual SectionType getType() = 0;

        // todo make section have reference to chunk
    };
}

#endif //LODESTONE_SECTION_H