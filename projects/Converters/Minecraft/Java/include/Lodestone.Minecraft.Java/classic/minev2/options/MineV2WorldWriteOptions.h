//
// Created by DexrnZacAttack on 11/20/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLDWRITEOPTIONS_H
#define LODESTONE_MINEV2WORLDWRITEOPTIONS_H
#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Conversion/world/options/AbstractWorldWriteOptions.h>
#include <Lodestone.Level/FiniteLevel.h>
#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::java::classic::minev2::options {
    struct MineV2WorldWriteOptions
        : public conversion::world::options::AbstractWorldWriteOptions {
        MineV2WorldWriteOptions() = default;

        explicit MineV2WorldWriteOptions(
            const common::registry::Identifier &level);

        common::registry::Identifier level =
            lodestone::level::world::World::Dimension::OVERWORLD;
    };
} // namespace lodestone::java::classic::minev2::options

#endif // LODESTONE_MINEV2WORLDWRITEOPTIONS_H