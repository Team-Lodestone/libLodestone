//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/block/instance/BlockInstance.h"
#include <memory>

namespace lodestone::level::block::instance {
    const map_t<common::registry::Identifier, level::properties::AbstractProperty *>
        BlockInstance::EMPTY_PROPERTIES{};

    BlockInstance::~BlockInstance() { delete m_properties; }

    const map_t<common::registry::Identifier, level::properties::AbstractProperty *> &
    BlockInstance::getProperties() const {
        if (!m_properties)
            return EMPTY_PROPERTIES;

        return *m_properties;
    }

    bool BlockInstance::hasProperty(const common::registry::Identifier &id) const {
        if (!m_properties)
            return false;

        return m_properties->contains(id);
    }

    const level::properties::AbstractProperty *
    BlockInstance::getProperty(const common::registry::Identifier &id) const {
        if (m_properties)
            if (const auto it = m_properties->find(id); it != m_properties->end())
                return it->second;

        if (const auto it = m_block->definition->defaultProperties.find(id); it != m_block->definition->defaultProperties.end())
            return it->second;

        return nullptr;
    }

    void BlockInstance::setProperty(
        const common::registry::Identifier &id, level::properties::AbstractProperty *property) {
        if (!m_properties)
            m_properties =
                new map_t<common::registry::Identifier, level::properties::AbstractProperty *>();

        m_properties->emplace(id, std::move(property));
    }

    const level::properties::AbstractProperty *
    BlockInstance::operator[](const common::registry::Identifier &id) const {
        return getProperty(id);
    }
} // namespace lodestone::level::block::properties