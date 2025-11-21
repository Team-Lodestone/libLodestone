//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_MATERIALS_H
#define LODESTONE_MATERIALS_H
#include "Lodestone.Level/material/Material.h"
#include <Lodestone.Common/Defines.h>

namespace lodestone::level::material {
    class LODESTONE_API MaterialRegistry {
      public:
        // todo: later
        static const Material AIR;
        static const Material STONE;
        static const Material GRASS;
        static const Material DIRT;
    };

    extern const Material *gMaterials;
} // namespace lodestone::level::material

#endif // LODESTONE_MATERIALS_H