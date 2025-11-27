//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCK_H
#define LODESTONE_BLOCK_H
#include <string>

#include "Lodestone.Level/material/Material.h"
#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Common/string/OperatorStringBuilder.h>
#include <Lodestone.Common/string/StringSerializable.h>

#include "Lodestone.Level/item/block/BlockItem.h"

namespace lodestone::level::block {
    class BlockState;

    class Block : public common::string::StringSerializable {
      public:
        constexpr Block(const common::registry::Identifier *id,
                        const material::Material &material)
            : mId(id), mMaterial(material) {
            this->mItem = new item::block::BlockItem(id, this);
        };

        constexpr ~Block() override = default;

        constexpr const common::registry::Identifier *getID() const {
            return mId;
        };

        constexpr std::string getIDString() const { return mId->getString(); };

        constexpr material::Material getMaterial() const { return mMaterial; }

        std::string toString() const override {
            return common::string::OperatorStringBuilder(typeid(*this))
                .addField("id", *mId)
                ->addField("material", mMaterial.toString())
                ->toString();
        };

        constexpr const item::block::BlockItem *getItem() const {
            return mItem;
        }

      private:
        const lodestone::common::registry::Identifier *mId;
        const item::block::BlockItem *mItem;
        const material::Material mMaterial;
    };
} // namespace lodestone::level::block

#endif // LODESTONE_BLOCK_H
