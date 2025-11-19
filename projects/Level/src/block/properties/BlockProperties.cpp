//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/block/properties/BlockProperties.h"
#include <memory>

namespace lodestone::level::block::properties {
    const map_t<std::string, level::properties::AbstractProperty *> BlockProperties::EMPTY_PROPERTIES{};

    BlockProperties::~BlockProperties() {
        delete mProperties;
    }

    const map_t<std::string, level::properties::AbstractProperty *> &BlockProperties::getProperties() const {
        if (!mProperties) return EMPTY_PROPERTIES;
        return *mProperties;
    }

    bool BlockProperties::hasProperty(const std::string &id) const {
        if (!mProperties) return false;
        return mProperties->contains(id);
    }

    const level::properties::AbstractProperty *BlockProperties::getProperty(const std::string &id) const {
        if (mProperties)
            if (const auto it = mProperties->find(id); it != mProperties->end())
                return it->second;

        return nullptr;
    }

    level::properties::AbstractProperty *BlockProperties::getProperty(const std::string &id) {
        if (mProperties)
            if (const auto it = mProperties->find(id); it != mProperties->end())
                return it->second;

        return nullptr;
    }

    void BlockProperties::setProperty(const std::string &id, level::properties::AbstractProperty *property) {
        if (!mProperties) mProperties = new map_t<std::string, level::properties::AbstractProperty*>();
        mProperties->emplace(id, std::move(property));
    }

    const level::properties::AbstractProperty *BlockProperties::operator[](const std::string &id) const {
        return getProperty(id);
    }

    level::properties::AbstractProperty *BlockProperties::operator[](const std::string &id) {
        return getProperty(id);
    }
}