//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTPROPERTIES_H
#define LODESTONE_ABSTRACTPROPERTIES_H
#include "Lodestone.Level/Identifiers.h"
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::level::properties {
    class AbstractProperty {
      protected:
        constexpr AbstractProperty() = default;

      public:
        constexpr virtual ~AbstractProperty() = default;

        constexpr virtual const lodestone::common::registry::Identifier *
        getTypeName() const {
            return &identifiers::properties::ABSTRACT_PROPERTY;
        };

        constexpr virtual size_t hash() const = 0;

        constexpr virtual bool equals(const AbstractProperty *rhs) const {
            if (rhs == nullptr)
                return false;

            if (typeid(rhs) != typeid(this))
                return false;

            return true;
        }

        template <typename T>
            requires std::is_base_of_v<AbstractProperty, T>
        constexpr const T *as() const {
            return dynamic_cast<const T *>(this);
        }

        constexpr bool operator==(const AbstractProperty &rhs) const {
            return this->equals(&rhs);
        }
    };
} // namespace lodestone::level::properties

#endif // LODESTONE_ABSTRACTPROPERTIES_H
