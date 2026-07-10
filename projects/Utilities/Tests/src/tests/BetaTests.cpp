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

#include <Lodestone.Conversion/block/VersionedBlockIO.h>
#include <Lodestone.Minecraft.Common/block/Blocks.h>
#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/util/ZipUtils.h"

namespace lodestone::tests::test {
    void BetaTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();
        mgr.addTest(READ_BETA_SERVER_WORLD, "Read Beta Server World (Zero)", readBetaServerWorld);
        mgr.addTest(WRITE_BETA_SUPERFLAT_WORLD, "Write Beta Superflat World", writeSuperflatWorld);
    }


    tfw::test::result::TestResult BetaTests::readBetaServerWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("BetaServerWorld");
        const std::filesystem::path inputFile(util::INPUT_FOLDER / "beta" / "b1.7.3" / "worlds" / (name + ".zip"));

        const std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / name;
        std::filesystem::remove_all(temp_dir);
        util::ZipUtils::extractAll(inputFile, temp_dir);

        logger << "Input: " << temp_dir << std::endl;

        const auto *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const
            minecraft::java::mcregion::world::McRegionWorldIo>(minecraft::java::identifiers::MCREGION_WORLD_IO);
        const auto wld = inputIo->read(
            minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                conversion::io::options::fs::FilesystemPathOptions{
                    temp_dir
                },
                conversion::io::options::versioned::VersionedOptions{
                    minecraft::java::Version::b1_3
                }
            });

        return tfw::test::result::TestResult(true, wld->toString());
    }

    tfw::test::result::TestResult BetaTests::writeSuperflatWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("SuperflatWorld");

        const std::filesystem::path outputFolder(
            util::OUTPUT_FOLDER / "converted" / "beta" / "b1.7.3" / "worlds" / name);
        std::filesystem::create_directories(outputFolder.parent_path());

        const auto wld = std::make_unique<level::world::World>();
        auto defaultLvl = std::make_unique<level::Level>();

        constexpr int bounds = 512;
        for (int x = -bounds; x < bounds; x++) {
            for (int z = -bounds; z < bounds; z++) {
                for (int y = 0; y < 4; y++) {
                    if (y == 0) {
                        defaultLvl->setBlockCreate(level::block::instance::BlockInstance(
                                                       &minecraft::common::block::Blocks::BEDROCK), x, y, z);
                    } else if (y < 3) {
                        defaultLvl->setBlockCreate(level::block::instance::BlockInstance(
                                                       &minecraft::common::block::Blocks::DIRT), x, y, z);
                    } else {
                        defaultLvl->setBlockCreate(level::block::instance::BlockInstance(
                                                       &minecraft::common::block::Blocks::GRASS_BLOCK), x, y, z);
                    }
                }
            }
        }
        wld->addLevel(level::world::World::Dimension::OVERWORLD, std::move(defaultLvl));

        const conversion::registry::WorldIORegistry &r = conversion::registry::WorldIORegistry::getInstance();
        const auto io = r.getAs<const minecraft::java::mcregion::world::McRegionWorldIo>(
            minecraft::java::identifiers::MCREGION_WORLD_IO);
        io->write(wld.get(),
                  lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                      lodestone::conversion::io::options::fs::FilesystemPathOptions{
                          outputFolder
                      },
                      conversion::io::options::versioned::VersionedOptions{
                          minecraft::java::b1_3
                      }
                  });
        return tfw::test::result::TestResult(true, wld->toString());
    }
}
