/** @file Registries.cpp
 *
 * @author DexrnZacAttack
 * @date 3/7/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.Conversion/registry/Registries.h"
#include "Lodestone.Conversion/registry/SingletonRegistry.h"

namespace lodestone::conversion::registry {
    template <const common::registry::Identifier *Identifier, typename Type, typename Stored>
    LODESTONE_CONVERSION_API SingletonRegistry<Identifier, Type, Stored> &SingletonRegistry<Identifier, Type, Stored>::getInstance() {
        static SingletonRegistry s_instance;
        return s_instance;
    }

    // I FOUGHT WITH THE GODDAMN COMPILER FOR 2 DAYS TRYING TO GET THIS SHIT TO WORK
    // THE FIX WAS JUST ME MAKING THE IDENTIFIER INSTANCES INLINE
    // AHIJSDHAISDHGIUYAGTSDUGUAYSDGUY
    IMPLEMENT_REGISTRY_ALIAS(SingletonRegistry<&identifiers::PLAYER_IO_REGISTRY, const io::interfaces::IPlayerIO>);
    IMPLEMENT_REGISTRY_ALIAS(SingletonRegistry<&identifiers::LEVEL_IO_REGISTRY, const io::interfaces::ILevelIO>);
    IMPLEMENT_REGISTRY_ALIAS(SingletonRegistry<&identifiers::CHUNK_IO_REGISTRY, const io::interfaces::IChunkIO>);
    IMPLEMENT_REGISTRY_ALIAS(SingletonRegistry<&identifiers::REGION_IO_REGISTRY, const io::interfaces::IRegionIO>);
    IMPLEMENT_REGISTRY_ALIAS(SingletonRegistry<&identifiers::WORLD_IO_REGISTRY, const io::interfaces::IWorldIO>);
}