//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEMINSTANCE_H
#define LODESTONE_ITEMINSTANCE_H
#include "Lodestone.Level/item/Item.h"
#include <Lodestone.Common/string/StringSerializable.h>
#include <gtl/phmap.hpp>

#include "Lodestone.Level/item/ItemRegistry.h"
#include "Lodestone.Level/properties/AbstractProperty.h"

namespace lodestone::level::item {
    class ItemInstance : public common::string::StringSerializable {
      public:
        static const map_t<std::string,
                           std::unique_ptr<properties::AbstractProperty>>
            EMPTY_PROPERTIES;

        ItemInstance(const Item *block) : m_item(block) {};

        ItemInstance(const common::registry::Identifier *id)
            : m_item(ItemRegistry::getInstance().getItem(id)) {};

        ItemInstance() : m_item(ItemRegistry::sDefaultItem) {}

        ~ItemInstance() override = default;

        const map_t<std::string,
                    std::unique_ptr<properties::AbstractProperty>> &
        getProperties() const;

        bool hasProperty(const std::string &id) const;

        const properties::AbstractProperty *
        getProperty(const std::string &id) const;

        properties::AbstractProperty *getProperty(const std::string &id);

        const Item *getItem() const { return m_item; }

        void
        setProperty(const std::string &id,
                    std::unique_ptr<properties::AbstractProperty> property);

        const properties::AbstractProperty *
        operator[](const std::string &id) const;

        properties::AbstractProperty *operator[](const std::string &id);

        bool operator==(const ItemInstance &b) const {
            return m_item == b.m_item && m_properties.has_value()
                       ? m_properties == b.m_properties
                       : m_properties.has_value() == b.m_properties.has_value();
        }

        std::string toString() const override {
            return std::format("ItemInstance[item={}]",
                               m_item->getID()->getString());
        };

      private:
        const Item *m_item;
        std::optional<
            map_t<std::string, std::unique_ptr<properties::AbstractProperty>>>
            m_properties;
    };
} // namespace lodestone::level::item

#endif // LODESTONE_ITEMINSTANCE_H
