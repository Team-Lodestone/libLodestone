//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_TEMPLATEDPROPERTY_H
#define LODESTONE_TEMPLATEDPROPERTY_H
#include "Lodestone.Level/properties/AbstractProperty.h"

namespace lodestone::level::properties {
    template <typename T>
    class TemplatedProperty final : public AbstractProperty {
      public:
        explicit constexpr TemplatedProperty(T val) : value(val) {}

        constexpr const lodestone::common::registry::Identifier *
        getTypeName() const override {
            return &identifiers::properties::TEMPLATED_PROPERTY;
        };

        T value;
    };
} // namespace lodestone::level::properties

#endif // LODESTONE_TEMPLATEDPROPERTY_H
