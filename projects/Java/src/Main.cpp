//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//

#include "Classic/ClassicBlockIo.h"
#include "Classic/MineV1LevelIo.h"
#include "Conversion/Level/LevelIORegistry.h"
#include "Main.h"

void lodestone_java_init() {
    lodestone::level::conversion::level::LevelIORegistry::sInstance->registerLevelIO("lodestone:minev1", new lodestone::java::classic::MineV1LevelIO());
}
