//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTPROPERTIES_H
#define LODESTONE_ABSTRACTPROPERTIES_H
#include <Lodestone.Common/registry/Identifier.h>
#include "Lodestone.Level/Identifiers.h"

namespace lodestone::level::properties {
    class AbstractProperty {
    protected:
        constexpr AbstractProperty() = default;
    public:
        constexpr virtual ~AbstractProperty() = default;

        constexpr virtual const lodestone::common::registry::Identifier *getTypeName() const {
            return &identifiers::properties::ABSTRACT_PROPERTY;
        };

        template <typename T>
        requires std::is_base_of_v<AbstractProperty, T>
        constexpr const T *as() const {
            return dynamic_cast<const T *>(this);
        }
    };
}

#endif //LODESTONE_ABSTRACTPROPERTIES_H
