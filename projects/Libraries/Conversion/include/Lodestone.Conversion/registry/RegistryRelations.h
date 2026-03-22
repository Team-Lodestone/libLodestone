//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_IORELATIONS_H
#define LODESTONE_IORELATIONS_H
#include "Lodestone.Conversion/io/IObjectIo.h"
#include <Lodestone.Common/registry/Identifier.h>

#include <type_traits>

namespace lodestone::conversion::registry {
     template<const common::registry::Identifier *_InternalIdentifier, typename _Type, const common::registry::Identifier *_RegistryIdentifier, typename _Registry>
     struct LODESTONE_CONVERSION_API RegistryIdentifierRelation {
        static constexpr const common::registry::Identifier *InternalIdentifier = _InternalIdentifier; // NOLINT
        static constexpr const common::registry::Identifier *RegistryIdentifier = _RegistryIdentifier; // NOLINT
        using Type = _Type;
        using Registry = _Registry;
    };

    template <typename... C>
    class LODESTONE_CONVERSION_API RegistryIdentifierRelations {
    public:
        template<typename T>
        T* getAsByRelation(const common::registry::Identifier *identifier) const requires (std::is_base_of_v<io::IObjectIO, typename C::Type> && ...) {
            static_assert((std::is_same_v<T, typename C::Type> || ...), "Given type was never registered in this relation");

            return (C::Registry::getInstance().template getAs<T>(*identifier), ...);
        }

        template<typename T, const common::registry::Identifier *_InternalIdentifier>
        T* getAsByRelation() const requires (std::is_base_of_v<io::IObjectIO, typename C::Type> && ...) {
            static_assert(((_InternalIdentifier == C::InternalIdentifier) || ...), "Given identifier was never registered in this relation");
            static_assert((std::is_same_v<T, typename C::Type> || ...), "Given type was never registered in this relation");

            return getInternal<T, _InternalIdentifier, C...>();
        }

        template<const common::registry::Identifier *_InternalIdentifier>
        io::IObjectIO* getByRelation() const requires (std::is_base_of_v<io::IObjectIO, typename C::Type> && ...) {
            static_assert(((_InternalIdentifier == C::InternalIdentifier) || ...), "Given identifier was never registered in this relation");

            return (C::Registry::getInstance().get(*C::RegistryIdentifier), ...);
        }

        io::IObjectIO* getByRelation(const common::registry::Identifier *identifier) const requires (std::is_base_of_v<io::IObjectIO, typename C::Type> && ...) {
            return this->template getByRelation<identifier>();
        }
    private:
        template<typename T, const common::registry::Identifier* _InternalIdentifier, typename Current, typename... Rest>
        T* getInternal() const {
            // array from temu
            if constexpr (_InternalIdentifier == Current::InternalIdentifier) {
                static_assert(std::is_same_v<T, typename Current::Type>, "Wrong type for given identifier");

                //we have our id
                return Current::Registry::getInstance().template getAs<T>(*Current::RegistryIdentifier);
            } else {
                if constexpr (sizeof...(Rest) <= 0) {
                    //we hit the end of the array
                    static_assert(sizeof...(Rest) > 0, "Given identifier was never registered in this relation");
                    return nullptr;
                }

                // continue onto next value
                return getInternal<T, _InternalIdentifier, Rest...>();
            }
        }
    };
}

#endif // LODESTONE_IORELATIONS_H
