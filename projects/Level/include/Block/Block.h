//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include <string>
#include <unordered_map>

#include "OperatorStringBuilder.h"
#include "Material/Material.h"

namespace lodestone::level::block {
    class BlockState;

    class Block {
    public:
        Block(const std::string &id, const material::Material material) : mId(id), mMaterial(material) {};

        operator std::string() const {
            return this->toString();
        }

        friend std::ostream& operator<<(std::ostream& os, const Block& block) {
            os << block.toString();
            return os;
        };

        std::string toString() const {
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

        // could maybe move these to a wrapper? unsure.

    private:
        std::string mId;
        const material::Material mMaterial;
    };
}

#endif //LODESTONE_BLOCK_H
