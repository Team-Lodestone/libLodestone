//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_REGISTRIES_H
#define LODESTONE_REGISTRIES_H
#include "Lodestone.Conversion/Identifiers.h"
#include "Lodestone.Conversion/io/interfaces/IChunkIo.h"
#include "Lodestone.Conversion/io/interfaces/ILevelIo.h"
#include "Lodestone.Conversion/io/interfaces/IPlayerIo.h"
#include "Lodestone.Conversion/io/interfaces/IWorldIo.h"
#include "Lodestone.Conversion/registry/SingletonRegistry.h"

//https://groups.google.com/g/android-ndk/c/xr_h7ediIhY
#define LODESTONE_CREATE_REGISTRY_ALIAS(name, type...) \
    extern template class type;                        \
    using name = type

#define LODESTONE_IMPLEMENT_REGISTRY_ALIAS(type...)    \
    template class type;

#define LODESTONE_IMPLEMENT_REGISTRY_GET_INSTANCE()                                                                          \
    template <const common::registry::Identifier *Identifier, typename Type, typename Stored>                                \
    LODESTONE_API SingletonRegistry<Identifier, Type, Stored> &SingletonRegistry<Identifier, Type, Stored>::getInstance() {  \
        static SingletonRegistry s_instance;                                                                                 \
        return s_instance;                                                                                                   \
    }

namespace lodestone::conversion::registry {
    LODESTONE_CREATE_REGISTRY_ALIAS(PlayerIORegistry, SingletonRegistry<&identifiers::PLAYER_IO_REGISTRY, const io::interfaces::IPlayerIO>);
    LODESTONE_CREATE_REGISTRY_ALIAS(LevelIORegistry, SingletonRegistry<&identifiers::LEVEL_IO_REGISTRY, const io::interfaces::ILevelIO>);
    LODESTONE_CREATE_REGISTRY_ALIAS(ChunkIORegistry, SingletonRegistry<&identifiers::CHUNK_IO_REGISTRY, const io::interfaces::IChunkIO>);
    LODESTONE_CREATE_REGISTRY_ALIAS(WorldIORegistry, SingletonRegistry<&identifiers::WORLD_IO_REGISTRY, const io::interfaces::IWorldIO>);
}

#endif // LODESTONE_REGISTRIES_H