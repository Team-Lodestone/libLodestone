//
// Created by DexrnZacAttack on 11/24/25 using zPc-i2.
//
#ifndef LODESTONE_REFLECTIVEPROPERTIES_H
#define LODESTONE_REFLECTIVEPROPERTIES_H
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/util/Casts.h>

#include <memory>

#include "Lodestone.Level/properties/AbstractProperty.h"
#include "Lodestone.Level/properties/TemplatedProperty.h"

namespace lodestone::level::properties {
    class ReflectiveProperties {
      public:
#define ADD_FIELD_PROPERTY(n, f)                                                  \
    case n##_hash:                                                             \
        return (typeid(decltype(f)) == typeid(f))                                        \
                   ? std::make_unique<                                         \
                         lodestone::level::properties::TemplatedProperty<decltype(f)>>(  \
                         f)                                                    \
                   : nullptr

        virtual ~ReflectiveProperties() = default;

        /** Gets a property by name
         *
         * This can be implemented in classes as effectively field reflection
         *
         * @property name The name of the property to get
         * @returns The property if present, otherwise nullptr.
         */
        virtual std::unique_ptr<AbstractProperty>
        getProperty(const std::string &name);

        template <typename T>
        std::unique_ptr<TemplatedProperty<T>> getProperty(const std::string &name) {
            return common::util::Casts::dynamic_unique_pointer_cast<TemplatedProperty<T>>(getProperty(name));
        }

        template <typename T>
        std::unique_ptr<TemplatedProperty<T>> getPropertyOr(const std::string &name, T value) {
            std::unique_ptr<TemplatedProperty<T>> prop = common::util::Casts::dynamic_unique_pointer_cast<TemplatedProperty<T>>(getProperty(name));
            if (prop == nullptr) {
                return std::make_unique<TemplatedProperty<T>>(value);
            }

            return std::move(prop);
        }
    };
} // namespace lodestone::level::properties

#endif // LODESTONE_REFLECTIVEPROPERTIES_H
