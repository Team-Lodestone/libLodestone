//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFT_COMMON_REGISTRIES_H
#define LODESTONE_MINECRAFT_COMMON_REGISTRIES_H
#include <Lodestone.Conversion/registry/Registries.h>

#include <Lodestone.Conversion/registry/SingletonRegistry.h>
#include "Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h"

#include "Lodestone.Minecraft.Common/Identifiers.h"
#include "Lodestone.Minecraft.Common/conversion/io/interfaces/ILevelDataIo.h"

namespace lodestone::conversion::registry {
    LODESTONE_CREATE_REGISTRY_ALIAS(LevelDataIORegistry, lodestone::conversion::registry::SingletonRegistry<&lodestone::minecraft::common::identifiers::registry::LEVEL_DATA_IO_REGISTRY, const lodestone::minecraft::common::conversion::io::interfaces::ILevelDataIO>);
    LODESTONE_CREATE_REGISTRY_ALIAS(RegionIORegistry, lodestone::conversion::registry::SingletonRegistry<&lodestone::minecraft::common::identifiers::registry::REGION_IO_REGISTRY, const lodestone::minecraft::common::conversion::io::interfaces::IRegionIO>);
}

#endif // LODESTONE_MINECRAFT_COMMON_REGISTRIES_H
