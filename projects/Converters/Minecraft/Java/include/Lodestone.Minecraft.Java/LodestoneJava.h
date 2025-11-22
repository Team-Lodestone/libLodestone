//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_MAIN_H
#define LODESTONE_MAIN_H
#include <Lodestone.Common/Defines.h>

#include <Lodestone.Conversion/block/VersionedBlockIO.h>

#include <Lodestone.Core/LodestoneExtension.h>

namespace lodestone::minecraft::java {
    class LODESTONE_API LodestoneJava : public core::LodestoneExtension {
      private:
        LodestoneJava();

      public:
        static LodestoneJava *getInstance();

        static void LODESTONE_API init();

        void initBlocks();

        lodestone::common::registry::Identifier getIdentifier() override;

        lodestone::conversion::block::version::VersionedBlockIO io;
    };
} // namespace lodestone::minecraft::java

#endif // LODESTONE_MAIN_H