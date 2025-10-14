//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include "Material/Material.h"

namespace lodestone::level::block {
    class Block {
    public:
        constexpr Block(const int id, const material::Material material) : mId(id), mMaterial(material) {};

        constexpr operator int() const {
            return getID();
        }

        constexpr operator material::Material() const {
            return getMaterial();
        }

        constexpr int getID() const {
            return mId;
        };

        constexpr material::Material getMaterial() const {
            return mMaterial;
        }
    private:
        const int mId;
        const material::Material mMaterial;
    };
}

#endif //LODESTONE_BLOCK_H
