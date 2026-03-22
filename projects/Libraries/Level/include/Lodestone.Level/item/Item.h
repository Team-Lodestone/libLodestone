//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEM_H
#define LODESTONE_ITEM_H
#include <format>
#include <string>

#include <Lodestone.Common/registry/Identifier.h>



#include "Lodestone.Level/properties/definition/ObjectDefinition.h"

namespace lodestone::level::block {
    class Block;
}

namespace lodestone::level::item {
    // cant wait to make io for this mmmmm
    class LODESTONE_LEVEL_API Item : public common::string::StringSerializable {
      public:
        explicit constexpr Item(
            const lodestone::common::registry::Identifier *id, const properties::definition::ObjectDefinition *definition,
            const int maxStack = 64)
            : m_id(id), m_maxStack(maxStack), m_definition(definition) {};

        constexpr ~Item() override = default;

        constexpr const lodestone::common::registry::Identifier *getID() const {
            return m_id;
        };

        constexpr std::string getIDString() const { return m_id->getString(); };

        std::string toString() const override {
            return std::format("Item[id={}]", *m_id);
        };

        constexpr int getMaxStack() const { return m_maxStack; }

      private:
        const lodestone::common::registry::Identifier *m_id;
        const int m_maxStack;

        const properties::definition::ObjectDefinition *m_definition;
    };
} // namespace lodestone::level::item

#endif // LODESTONE_ITEM_H
