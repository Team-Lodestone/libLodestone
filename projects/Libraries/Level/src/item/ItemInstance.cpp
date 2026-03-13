//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Level/item/ItemInstance.h"

namespace lodestone::level::item {
    const map_t<std::string, std::unique_ptr<properties::AbstractProperty>>
        ItemInstance::EMPTY_PROPERTIES{};

    const map_t<std::string, std::unique_ptr<properties::AbstractProperty>> &
    ItemInstance::getProperties() const {
        if (!m_properties)
            return EMPTY_PROPERTIES;
        return *m_properties;
    }

    bool ItemInstance::hasProperty(const std::string &id) const {
        if (!m_properties)
            return false;
        return m_properties->contains(id);
    }

    const properties::AbstractProperty *
    ItemInstance::getProperty(const std::string &id) const {
        if (m_properties)
            if (const auto it = m_properties->find(id); it != m_properties->end())
                return it->second.get();

        return nullptr;
    }

    properties::AbstractProperty *
    ItemInstance::getProperty(const std::string &id) {
        if (m_properties)
            if (const auto it = m_properties->find(id); it != m_properties->end())
                return it->second.get();

        return nullptr;
    }

    void ItemInstance::setProperty(
        const std::string &id,
        std::unique_ptr<properties::AbstractProperty> property) {
        if (!m_properties)
            m_properties =
                map_t<std::string,
                      std::unique_ptr<properties::AbstractProperty>>();
        m_properties->emplace(id, std::move(property));
    }

    const properties::AbstractProperty *
    ItemInstance::operator[](const std::string &id) const {
        return getProperty(id);
    }

    properties::AbstractProperty *
    ItemInstance::operator[](const std::string &id) {
        return getProperty(id);
    }
} // namespace lodestone::level::item
