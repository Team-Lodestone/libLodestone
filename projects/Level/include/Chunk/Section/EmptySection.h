//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYSECTION_H
#define LODESTONE_EMPTYSECTION_H
#include "Section.h"
#include "Block/State/BlockState.h"

namespace lodestone::level::chunk::section {
    class EmptySection : public Section {
    public:
        static EmptySection *sInstance;

        SectionType getType() override;

        const block::state::BlockState * getBlocks() override;

        const uint8_t * getBlockLight() const override;

        const uint8_t * getSkyLight() const override;

        block::state::BlockState *getBlock(const int x, const int y, const int z) const override;
    };
}

#endif //LODESTONE_EMPTYSECTION_H
