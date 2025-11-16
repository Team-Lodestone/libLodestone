//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEM_H
#define LODESTONE_ITEM_H
#include <format>
#include <string>

#include <Lodestone.Common/registry/Identifier.h>

#include <Lodestone.Common/string/OperatorStringBuilder.h>

namespace lodestone::level::block {
    class Block;
}

namespace lodestone::level::item {
    // cant wait to make io for this mmmmm
    class Item : public common::string::StringSerializable {
    public:
        explicit constexpr Item(const lodestone::common::registry::Identifier *id, const int maxStack = 64) : mId(id), mMaxStack(maxStack) {
        };

        constexpr ~Item() override = default;

        constexpr const lodestone::common::registry::Identifier *getID() const {
            return mId;
        };

        constexpr std::string getIDString() const {
            return mId->getString();
        };

        std::string toString() const override {
            return (common::string::OperatorStringBuilder(typeid(*this)))
                .addField("id", this->getID())
                ->toString();
        };

        constexpr int getMaxStack() const {
            return mMaxStack;
        }

    private:
        const lodestone::common::registry::Identifier *mId;
        const int mMaxStack;
    };
}

#endif //LODESTONE_ITEM_H
