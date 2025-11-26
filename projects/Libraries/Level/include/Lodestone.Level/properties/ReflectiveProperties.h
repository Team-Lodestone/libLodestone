//
// Created by DexrnZacAttack on 11/24/25 using zPc-i2.
//
#ifndef LODESTONE_REFLECTIVEPROPERTIES_H
#define LODESTONE_REFLECTIVEPROPERTIES_H
#include <memory>

#include "Lodestone.Level/properties/AbstractProperty.h"
#include "Lodestone.Level/properties/TemplatedProperty.h"

namespace lodestone::level::properties {
    class ReflectiveProperties {
    public:
        // oh no nfts
#define ADD_PROPERTY(n, f, t) case n##_hash: return (typeid(t) == typeid(f)) ? std::make_shared<lodestone::level::properties::TemplatedProperty<t>>(f) : nullptr

        virtual ~ReflectiveProperties() = default;

        /** Gets a property by name
         *
         * This can be implemented in classes as effectively field reflection
         *
         * @property name The name of the property to get
         * @returns The property if present, otherwise nullptr.
         */
        virtual std::shared_ptr<level::properties::AbstractProperty> getProperty(const std::string &name) = 0;
    };
}

#endif // LODESTONE_REFLECTIVEPROPERTIES_H
