//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"

namespace lodestone::level::block::instance {
    ImmutableBlockInstance::ImmutableBlockInstance()
        : BlockInstance(BlockRegistry::s_defaultBlock) {}

    ImmutableBlockInstance *ImmutableBlockInstance::getInstance() {
        static ImmutableBlockInstance s_instance;
        return &s_instance;
    }

    bool ImmutableBlockInstance::hasProperty(const common::registry::Identifier &id) const {
        return false;
    }

    const level::properties::AbstractProperty *
    ImmutableBlockInstance::getProperty(const common::registry::Identifier &id) const {
        return nullptr;
    }

    void ImmutableBlockInstance::setProperty(
        const common::registry::Identifier &id, level::properties::AbstractProperty *property) {}

    const level::properties::AbstractProperty *
    ImmutableBlockInstance::operator[](const common::registry::Identifier &id) const {
        return nullptr;
    }
} // namespace lodestone::level::block::properties
