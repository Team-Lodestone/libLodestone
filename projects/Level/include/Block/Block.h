//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include <string>
#include <unordered_map>

#include "OperatorStringBuilder.h"
#include "StringSerializable.h"
#include "Material/Material.h"

namespace lodestone::level::block {
    class BlockState;

    class Block : public StringSerializable {
    public:
        Block(const std::string &id, const material::Material material) : mId(id), mMaterial(material) {};

        std::string toString() const override {
            return (new OperatorStringBuilder(typeid(*this)))
            ->ADD_FIELD(mId)
            ->ADD_FIELD(mMaterial)
            ->toString();
        }

        constexpr const std::string &getID() const {
            return mId;
        };

        constexpr material::Material getMaterial() const {
            return mMaterial;
        }

    private:
        std::string mId;
        const material::Material mMaterial;
    };
}

#endif //LODESTONE_BLOCK_H
