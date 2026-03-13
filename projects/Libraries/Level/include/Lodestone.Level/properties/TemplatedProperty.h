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
        explicit constexpr TemplatedProperty(T val) : m_value(val) {}

        constexpr const lodestone::common::registry::Identifier *
        getTypeName() const override {
            return &identifiers::properties::TEMPLATED_PROPERTY;
        };

        constexpr const T &getValue() const { return m_value; };

        constexpr operator const T &() const { return m_value; }

        constexpr size_t hash() const override {
            return std::hash<T>()(m_value) ^
                   (std::hash<const lodestone::common::registry::Identifier
                                  *>()(getTypeName())
                    << 8);
        }

        constexpr bool equals(const AbstractProperty *rhs) const override {
            if (!AbstractProperty::equals(rhs))
                return false;

            const TemplatedProperty *t = dynamic_cast<const TemplatedProperty *>(rhs);

            return typeid(t->m_value) == typeid(this->m_value)
                && t->m_value == this->m_value;
        }

    private:
        T m_value;
    };
} // namespace lodestone::level::properties

#endif // LODESTONE_TEMPLATEDPROPERTY_H
