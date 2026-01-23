//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "Lodestone.Level/block/properties/ImmutableBlockProperties.h"

namespace lodestone::level::block::properties {
    ImmutableBlockProperties::ImmutableBlockProperties()
        : BlockProperties(BlockRegistry::sDefaultBlock) {}

    ImmutableBlockProperties *ImmutableBlockProperties::getInstance() {
        static ImmutableBlockProperties sInstance;
        return &sInstance;
    }

    bool ImmutableBlockProperties::hasProperty(const std::string &id) const {
        return false;
    }

    const level::properties::AbstractProperty *
    ImmutableBlockProperties::getProperty(const std::string &id) const {
        return nullptr;
    }

    level::properties::AbstractProperty *
    ImmutableBlockProperties::getProperty(const std::string &id) {
        return nullptr;
    }

    void ImmutableBlockProperties::setProperty(
        const std::string &id, level::properties::AbstractProperty *property) {}

    const level::properties::AbstractProperty *
    ImmutableBlockProperties::operator[](const std::string &id) const {
        return nullptr;
    }

    level::properties::AbstractProperty *
    ImmutableBlockProperties::operator[](const std::string &id) {
        return nullptr;
    }
} // namespace lodestone::level::block::properties
