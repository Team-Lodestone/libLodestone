//
// Created by DexrnZacAttack on 2/15/26 using zPc-i2.
//
#ifndef LODESTONE_SINGLETONREGISTRY_H
#define LODESTONE_SINGLETONREGISTRY_H
#include <Lodestone.Common/registry/Identifier.h>
#include "Lodestone.Conversion/registry/SimpleRegistry.h"

namespace lodestone::conversion::registry {
    template <const common::registry::Identifier *Identifier, typename Type, typename Stored = std::unique_ptr<const Type>>
    class LODESTONE_CONVERSION_API SingletonRegistry : public SimpleRegistry<Identifier, Type, Stored> {
    public:
        static LODESTONE_CONVERSION_API SingletonRegistry &getInstance();

        SingletonRegistry(const SingletonRegistry&) = delete;
        SingletonRegistry& operator=(const SingletonRegistry&) = delete;
        SingletonRegistry(SingletonRegistry&&) = delete;
        SingletonRegistry& operator=(SingletonRegistry&&) = delete;

    protected:
        SingletonRegistry() = default;
        ~SingletonRegistry() = default;
    };
}

#endif // LODESTONE_SINGLETONREGISTRY_H