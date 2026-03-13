//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_REGISTRIES_H
#define LODESTONE_REGISTRIES_H
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/SingletonRegistry.h>

#include "Lodestone.Minecraft.Common/Identifiers.h"
#include "Lodestone.Minecraft.Common/conversion/io/interfaces/ILevelDataIo.h"

namespace lodestone::minecraft::common::conversion::registry {
    CREATE_REGISTRY_ALIAS(LevelDataIORegistry, lodestone::conversion::registry::SingletonRegistry<&identifiers::LEVEL_DATA_IO_REGISTRY, const io::interfaces::ILevelDataIO>);
}

#endif // LODESTONE_REGISTRIES_H
