//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_FINITELEVEL_H
#define LODESTONE_FINITELEVEL_H
#include "Level.h"
#include "Lodestone.Level/types/Bounds2i.h"

namespace lodestone::level {
    class LODESTONE_API FiniteLevel : public Level {
    public:
        // TODO regular Level to FiniteLevel
        explicit FiniteLevel(const types::Bounds2i &bounds);

        bool isChunkInBounds(const types::Vec2i &coords) override;

        const types::Bounds2i &getBounds() const;
    protected:
        // todo: 3d finite???
        types::Bounds2i mBounds;
    };
}

#endif //LODESTONE_FINITELEVEL_H
