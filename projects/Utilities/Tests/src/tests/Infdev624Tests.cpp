//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/Infdev624Tests.h"

#include <filesystem>
#include <Lodestone.Conversion/io/options/fs/FilesystemPathOptions.h>
#include <Lodestone.Conversion/io/options/versioned/VersionedOptions.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Level/world/World.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include <Lodestone.Minecraft.Java/Identifiers.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/conversion/infdev/InfdevWorldIo.h>
#include <TestFramework/TestFramework.h>

#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/util/ZipUtils.h"

namespace lodestone::tests::test {
    void Infdev624Tests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_INFDEV_624_WORLD4, "Read Infdev 624 World4 (Zero)", readWorld4);
    }

    tfw::test::result::TestResult Infdev624Tests::readWorld4(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("World4");
        const std::filesystem::path inputFile(util::INPUT_FOLDER / "infdev" / "inf-20100624" / "worlds" / (name + ".zip"));

        // Remove and extract to temporary directory
        const std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / name;
        std::filesystem::remove_all(temp_dir);
        util::ZipUtils::extractAll(inputFile, temp_dir);

        logger << "Input: " << temp_dir << std::endl;

        const auto *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::infdev::world::InfdevWorldIo>(minecraft::java::identifiers::INF_624_WORLD_IO);
        const auto w = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                temp_dir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::Version::inf20100624
            }
        });
        return tfw::test::result::TestResult(true, w->toString());
    }
}
