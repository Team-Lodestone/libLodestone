//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/AlphaTests.h"

#include <filesystem>

#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/conversion/alpha/AlphaWorldIo.h>
#include <TestFramework/TestFramework.h>
#include <TestFramework/test/logging/loggers/ITestLogger.h>
#include <TestFramework/test/result/TestResult.h>
#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/util/Visualizer.h"
#include "Lodestone.Tests/util/ZipUtils.h"

namespace lodestone::tests::test {
    void AlphaTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_SNOW_WORLD_ZERO, "Read Snow World (Zero)", readSnowWorldZero);
        mgr.addTest(READ_NETHER_WORLD_ZERO, "Read Nether World (Zero)", readNetherWorldZero);
    }

    tfw::test::result::TestResult AlphaTests::readSnowWorldZero(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("SnowWorldZero");
        const std::filesystem::path inputFile(util::INPUT_FOLDER / "alpha" / "a1.1.2_01" / "worlds" / (name + ".zip"));

        const std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / name;

        std::filesystem::remove_all(temp_dir);

        util::ZipUtils::extractAll(inputFile, temp_dir);

        logger << "Input: " << temp_dir << std::endl;

        const auto *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::alpha::world::AlphaWorldIo>(minecraft::java::identifiers::ALPHA_WORLD_IO);
        const auto wld = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                temp_dir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::Version::inf20100629
            }
        });

        return tfw::test::result::TestResult(true, wld->toString());
    }

    tfw::test::result::TestResult AlphaTests::readNetherWorldZero(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("NetherWorldZero");
        const std::filesystem::path inputFile(util::INPUT_FOLDER / "alpha" / "a1.2.6" / "worlds" / (name + ".zip"));

        // Remove and extract to temporary directory
        const std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / name;
        std::filesystem::remove_all(temp_dir);
        util::ZipUtils::extractAll(inputFile, temp_dir);

        logger << "Input: " << temp_dir << std::endl;

        const auto *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::alpha::world::AlphaWorldIo>(minecraft::java::identifiers::ALPHA_WORLD_IO);
        const auto wld = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                temp_dir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::Version::inf20100629
            }
        });

        return tfw::test::result::TestResult(true, wld->toString());
    }
}
