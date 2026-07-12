//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_MAIN_H
#define LODESTONE_MAIN_H
#include <Lodestone.Common/registry/Identifiable.h>
#include <Lodestone.Common/registry/Identifier.h>

#include <Lodestone.Common/Defines.h>

#include <Lodestone.Conversion/block/VersionedBlockIO.h>

#include <Lodestone.Core/LodestoneExtension.h>
#include <Lodestone.Common/util/Semver.h>


namespace lodestone::minecraft::java {
    inline static constexpr lodestone::common::registry::Identifier IDENTIFIER = {"lodestone", "minecraft/java"};
    static constexpr lodestone::common::util::Semver VERSION = {
        LODESTONE_MINECRAFT_JAVA_MAJOR_VERSION,
        LODESTONE_MINECRAFT_JAVA_MINOR_VERSION,
        LODESTONE_MINECRAFT_JAVA_PATCH_VERSION,
        LODESTONE_MINECRAFT_JAVA_DEV_VERSION
    };

    class LODESTONE_API LodestoneJava : public core::LodestoneExtension, public lodestone::common::registry::Identifiable<&IDENTIFIER> {
      private:
        LodestoneJava();

      public:
        static LodestoneJava *getInstance();

        void initBlocks();
        void initItems();

        lodestone::common::registry::Identifier getIdentifier() const override;
        lodestone::common::util::Semver getVersion() const override;

        lodestone::conversion::block::version::VersionedBlockIO m_blockIo;
    };

#ifndef __EMSCRIPTEN__
    extern "C" {
        core::LodestoneExtension *lodestoneInit();
    }
#endif
} // namespace lodestone::minecraft::java

#endif // LODESTONE_MAIN_H