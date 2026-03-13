//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_REGISTRIES_H
#define LODESTONE_REGISTRIES_H
#include "Lodestone.Conversion/Identifiers.h"
#include "Lodestone.Conversion/io/interfaces/IChunkIo.h"
#include "Lodestone.Conversion/io/interfaces/ILevelIo.h"
#include "Lodestone.Conversion/io/interfaces/IPlayerIo.h"
#include "Lodestone.Conversion/io/interfaces/IRegionIo.h"
#include "Lodestone.Conversion/io/interfaces/IWorldIo.h"
#include "Lodestone.Conversion/registry/SimpleRegistry.h"
#include "Lodestone.Conversion/registry/SingletonRegistry.h"

namespace lodestone::conversion::registry {
//https://groups.google.com/g/android-ndk/c/xr_h7ediIhY
#define CREATE_REGISTRY_ALIAS(name, type...) \
    extern template class type;              \
    using name = type

#define IMPLEMENT_REGISTRY_ALIAS(type...)  \
    template class type;

    CREATE_REGISTRY_ALIAS(PlayerIORegistry, SingletonRegistry<&identifiers::PLAYER_IO_REGISTRY, const io::interfaces::IPlayerIO>);
    CREATE_REGISTRY_ALIAS(LevelIORegistry, SingletonRegistry<&identifiers::LEVEL_IO_REGISTRY, const io::interfaces::ILevelIO>);
    CREATE_REGISTRY_ALIAS(ChunkIORegistry, SingletonRegistry<&identifiers::CHUNK_IO_REGISTRY, const io::interfaces::IChunkIO>);
    CREATE_REGISTRY_ALIAS(RegionIORegistry, SingletonRegistry<&identifiers::REGION_IO_REGISTRY, const io::interfaces::IRegionIO>);
    CREATE_REGISTRY_ALIAS(WorldIORegistry, SingletonRegistry<&identifiers::WORLD_IO_REGISTRY, const io::interfaces::IWorldIO>);
}

#endif // LODESTONE_REGISTRIES_H