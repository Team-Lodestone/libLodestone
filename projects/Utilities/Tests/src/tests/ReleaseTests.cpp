//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/ReleaseTests.h"

#include <TestFramework/TestFramework.h>

#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilWorldIo.h>
#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/util/ZipUtils.h"

namespace lodestone::tests::test {
    void ReleaseTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_SNOW_RELEASE_WORLD_ZERO, "Read Snow r1.2.5 World (Zero)", readSnowReleaseWorldZero);
    }


    tfw::test::result::TestResult ReleaseTests::readSnowReleaseWorldZero(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("SnowReleaseWorldZero");
        const std::filesystem::path inputFile(util::INPUT_FOLDER / "release" / "r1.2.5" / "worlds" / (name + ".zip"));

        const std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / name;
        std::filesystem::remove_all(temp_dir);
        util::ZipUtils::extractAll(inputFile, temp_dir);

        logger << "Input: " << temp_dir << std::endl;

        const auto *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::anvil::jungle::world::JungleAnvilWorldIo>(minecraft::java::identifiers::ANVIL_JUNGLE_WORLD_IO);
        const auto wld = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                temp_dir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::Version::r1_2_1
            }
        });

        return tfw::test::result::TestResult(true, wld->toString());
    }
}
