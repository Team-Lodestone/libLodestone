//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include <string>

#include <Lodestone.Common/String/OperatorStringBuilder.h>
#include <Lodestone.Common/String/StringSerializable.h>
#include "Lodestone.Level/Material/Material.h"
#include "Lodestone.Level/Registry/NamespacedString.h"

namespace lodestone::level::block {
    class BlockState;

    class Block {
    public:
        constexpr Block(const registry::NamespacedString &id, const material::Material material) : mId(id), mMaterial(material) {};

        constexpr const std::string &getID() const {
            return mId;
        };

        constexpr material::Material getMaterial() const {
            return mMaterial;
        };

    private:
        const std::string mId;
        const material::Material mMaterial;
    };
}

#endif //LODESTONE_BLOCK_H
