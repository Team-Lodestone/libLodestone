/** @file Registries.cpp
 *
 * @author DexrnZacAttack
 * @date 4/2/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.Minecraft.Common/conversion/registry/Registries.h"

namespace lodestone::conversion::registry {
    LODESTONE_IMPLEMENT_REGISTRY_GET_INSTANCE()

    LODESTONE_IMPLEMENT_REGISTRY_ALIAS(lodestone::conversion::registry::SingletonRegistry<&lodestone::minecraft::common::identifiers::registry::REGION_IO_REGISTRY, const lodestone::minecraft::common::conversion::io::interfaces::IRegionIO>);
    LODESTONE_IMPLEMENT_REGISTRY_ALIAS(lodestone::conversion::registry::SingletonRegistry<&lodestone::minecraft::common::identifiers::registry::LEVEL_DATA_IO_REGISTRY, const lodestone::minecraft::common::conversion::io::interfaces::ILevelDataIO>);
}