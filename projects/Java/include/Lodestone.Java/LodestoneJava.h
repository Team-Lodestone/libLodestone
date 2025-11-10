//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_MAIN_H
#define LODESTONE_MAIN_H
#include <Lodestone.Common/Defines.h>

#include <Lodestone.Level/conversion/block/VersionedBlockIO.h>

namespace lodestone::java {
    class LODESTONE_API LodestoneJava {
    private:
        LodestoneJava();

        static LodestoneJava *sInstance;

    public:
        static LodestoneJava *getInstance();

        static void LODESTONE_API init();

        void initBlocks();

        level::conversion::block::version::VersionedBlockIO io;
    };
}

#endif //LODESTONE_MAIN_H