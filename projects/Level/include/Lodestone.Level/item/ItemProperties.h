//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEMPROPERTIES_H
#define LODESTONE_ITEMPROPERTIES_H
#include "Lodestone.Level/item/Item.h"
#include <gtl/phmap.hpp>
#include <Lodestone.Common/string/StringSerializable.h>

#include "Lodestone.Level/item/ItemRegistry.h"
#include "Lodestone.Level/properties/AbstractProperty.h"

namespace lodestone::level::item {
    class ItemProperties : public common::string::StringSerializable {
    public:
        static const map_t<std::string, std::unique_ptr<properties::AbstractProperty>> EMPTY_PROPERTIES;

        ItemProperties(const Item *block) : mItem(block) {
        };

        ItemProperties(const common::registry::Identifier *id) : mItem(
            ItemRegistry::getInstance().getItem(id)) {
        };

        ItemProperties() : mItem(ItemRegistry::sDefaultItem) {
        }

        ~ItemProperties() override = default;

        const map_t<std::string, std::unique_ptr<properties::AbstractProperty>> &getProperties() const;

        bool hasProperty(const std::string &id) const;

        const properties::AbstractProperty *getProperty(const std::string &id) const;

        properties::AbstractProperty *getProperty(const std::string &id);

        const Item *getItem() const { return mItem; }

        void setProperty(const std::string &id, std::unique_ptr<properties::AbstractProperty> property);

        const properties::AbstractProperty *operator[](const std::string &id) const;

        properties::AbstractProperty *operator[](const std::string &id);

        bool operator==(const ItemProperties &b) const {
            return mItem == b.mItem && mProperties.has_value() ? mProperties == b.mProperties : mProperties.has_value() == b.mProperties.has_value();
        }

        constexpr std::string toString() const override {
            return std::format("ItemProperties[block={}]", mItem->getID()->getString());
        };

    private:
        const Item *mItem;
        std::optional<map_t<std::string, std::unique_ptr<properties::AbstractProperty>>> mProperties;
    };
}

#endif //LODESTONE_ITEMPROPERTIES_H
