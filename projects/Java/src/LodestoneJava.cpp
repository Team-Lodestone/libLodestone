//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//

#include <Lodestone.Level/Conversion/Level/LevelIORegistry.h>

#include "Classic/MineV1/MineV1LevelIo.h"
#include "Classic/MineV2/MineV2LevelIO.h"
#include "LodestoneJava.h"

void lodestone_java_init() {
    lodestone::level::conversion::level::LevelIORegistry::sInstance->registerLevelIO("lodestone:minev1", new lodestone::java::classic::minev1::MineV1LevelIO());
    lodestone::level::conversion::level::LevelIORegistry::sInstance->registerLevelIO("lodestone:minev2", new lodestone::java::classic::minev2::MineV2LevelIO());
}
