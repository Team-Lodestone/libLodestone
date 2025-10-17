//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include <string>

#include <Lodestone.Common/String/OperatorStringBuilder.h>
#include <Lodestone.Common/String/StringSerializable.h>
#include "Lodestone.Level/Material/Material.h"

namespace lodestone::level::block {
    class BlockState;

    class Block : public StringSerializable {
    public:
        Block(const std::string &id, const material::Material material) : mId(id), mMaterial(material) {};

        constexpr const std::string &getID() const {
            return mId;
        };

        constexpr material::Material getMaterial() const {
            return mMaterial;
        };

        std::string toString() const override;

    private:
        std::string mId;
        const material::Material mMaterial;
    };
}

#endif //LODESTONE_BLOCK_H
