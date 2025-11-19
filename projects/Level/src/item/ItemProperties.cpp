//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Level/item/ItemProperties.h"

namespace lodestone::level::item {
    const map_t<std::string, std::unique_ptr<properties::AbstractProperty>> ItemProperties::EMPTY_PROPERTIES{};

    const map_t<std::string, std::unique_ptr<properties::AbstractProperty>> &ItemProperties::getProperties() const {
        if (!mProperties) return EMPTY_PROPERTIES;
        return *mProperties;
    }

    bool ItemProperties::hasProperty(const std::string &id) const {
        if (!mProperties) return false;
        return mProperties->contains(id);
    }

    const properties::AbstractProperty *ItemProperties::getProperty(const std::string &id) const {
        if (mProperties)
            if (const auto it = mProperties->find(id); it != mProperties->end())
                return it->second.get();

        return nullptr;
    }

    properties::AbstractProperty *ItemProperties::getProperty(const std::string &id) {
        if (mProperties)
            if (const auto it = mProperties->find(id); it != mProperties->end())
                return it->second.get();

        return nullptr;
    }


    void ItemProperties::setProperty(const std::string &id, std::unique_ptr<properties::AbstractProperty> property) {
        if (!mProperties) mProperties = map_t<std::string, std::unique_ptr<properties::AbstractProperty>>();
        mProperties->emplace(id, std::move(property));
    }

    const properties::AbstractProperty *ItemProperties::operator[](const std::string &id) const {
        return getProperty(id);
    }

    properties::AbstractProperty *ItemProperties::operator[](const std::string &id) {
        return getProperty(id);
    }
}
