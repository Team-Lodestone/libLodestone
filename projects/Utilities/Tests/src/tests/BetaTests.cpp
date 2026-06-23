//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/BetaTests.h"

#include <filesystem>
#include <TestFramework/TestFramework.h>

#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/conversion/mcregion/McRegionWorldIo.h>
#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/util/ZipUtils.h"

namespace lodestone::tests::test {
    void BetaTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();
        mgr.addTest(READ_BETA_SERVER_WORLD, "Read Beta Server World (Zero)", readBetaServerWorld);
    }


    tfw::test::result::TestResult BetaTests::readBetaServerWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("BetaServerWorld");
        const std::filesystem::path inputFile(util::INPUT_FOLDER / "beta" / "b1.7.3" / "worlds" / (name + ".zip"));

        const std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / name;
        std::filesystem::remove_all(temp_dir);
        util::ZipUtils::extractAll(inputFile, temp_dir);

        logger << "Input: " << temp_dir << std::endl;

        const auto *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::mcregion::world::McRegionWorldIo>(minecraft::java::identifiers::MCREGION_WORLD_IO);
        const auto wld = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                temp_dir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::Version::b1_3
            }
        });

        return tfw::test::result::TestResult(true, wld->toString());
    }
}
