//
// Created by DexrnZacAttack on 11/20/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLDWRITEOPTIONS_H
#define LODESTONE_MINEV2WORLDWRITEOPTIONS_H
#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Level/FiniteLevel.h>
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Conversion/io/options/OptionsBuilder.h>

namespace lodestone::minecraft::java::classic::minev2::options {
    struct MineV2WorldWriteOptions : conversion::io::options::IOptions {
        lodestone::common::registry::Identifier level = lodestone::level::world::World::Dimension::OVERWORLD;

        explicit MineV2WorldWriteOptions(const lodestone::common::registry::Identifier &level);
    };
} // namespace lodestone::minecraft::java::classic::minev2::options

#endif // LODESTONE_MINEV2WORLDWRITEOPTIONS_H