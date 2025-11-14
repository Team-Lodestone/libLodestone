//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include <string>

#include <Lodestone.Common/string/OperatorStringBuilder.h>
#include <Lodestone.Common/string/StringSerializable.h>
#include "Lodestone.Level/material/Material.h"
#include <Lodestone.Common/registry/NamespacedString.h>

namespace lodestone::level::block {
    class BlockState;

    class Block : public common::string::StringSerializable {
    public:
        constexpr Block(const lodestone::common::registry::NamespacedString *id,
                        const material::Material &material) : mId(id), mMaterial(material) {
        };

        constexpr ~Block() override = default;

        constexpr const lodestone::common::registry::NamespacedString *getID() const {
            return mId;
        };

        constexpr std::string getIDString() const {
            return mId->getString();
        };

        constexpr material::Material getMaterial() const {
            return mMaterial;
        }

        constexpr std::string toString() const override {
            return std::format("Block[id={},material={}]", *mId, mMaterial.toString());
        };

    private:
        const lodestone::common::registry::NamespacedString *mId;
        const material::Material mMaterial;
    };
}

#endif //LODESTONE_BLOCK_H
