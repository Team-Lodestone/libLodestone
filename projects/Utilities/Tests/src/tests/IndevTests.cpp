//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/IndevTests.h"

#include <filesystem>
#include <libnbt++/io/izlibstream.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIO.h>
#include <TestFramework/TestFramework.h>

#include <Lodestone.Minecraft.Java/conversion/mcregion/McRegionWorldIo.h>

#include <Lodestone.Minecraft.Java/conversion/classic/minev1/MineV1LevelIO.h>
#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/util/Visualizer.h"

namespace lodestone::tests::test {
    void IndevTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_INDEV_HUGE_FLOATING, "Read Indev Huge Floating World (Zero)", readHugeFloatingWorld);
        mgr.addTest(WRITE_CLASSIC_WORLD_ZERO, "Write Classic World (Zero)", writeClassicWorldZero);
    }

    tfw::test::result::TestResult IndevTests::readHugeFloatingWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name = "huge_floating";
        const std::filesystem::path inputFile = util::INPUT_FOLDER / "indev" / "in-20100223" / "worlds" / (name + ".mclevel");

        logger << inputFile << std::endl;

        std::ifstream strm(inputFile, std::ios::binary);
        zlib::izlibstream zstrm(strm);

        const auto *inputIo = conversion::registry::LevelIORegistry::getInstance().getAs<const
            minecraft::java::indev::McLevelLevelIO>(minecraft::java::identifiers::MCLEVEL_LEVEL_IO);

        auto lvl = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonReadOptions {
            conversion::io::options::fs::file::FileReaderOptions{
                zstrm
            },
            conversion::io::options::versioned::VersionedOptions{
                minecraft::java::Version::in20100219
            }
        });

        auto wld = new level::world::World();
        wld->addLevel(level::world::World::Dimension::OVERWORLD, std::move(lvl));

        const conversion::registry::WorldIORegistry &r = conversion::registry::WorldIORegistry::getInstance();

        const auto io = r.getAs<const minecraft::java::mcregion::world::McRegionWorldIo>(
                minecraft::java::identifiers::MCREGION_WORLD_IO);
        const std::filesystem::path outputFolder = util::OUTPUT_FOLDER / "converted" / "beta" / "indev" / "in-20100223" / "worlds" / name;

        std::filesystem::create_directories(outputFolder);

        io->write(wld, lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
                      lodestone::conversion::io::options::fs::FilesystemPathOptions {
                          outputFolder
                      },
                      conversion::io::options::versioned::VersionedOptions {
                          minecraft::java::b1_3
                      }
                  });
        util::Visualizer visualizer;
        visualizer.createMap(wld);

        return tfw::test::result::TestResult(true, wld->toString());
    }

    tfw::test::result::TestResult IndevTests::writeClassicWorldZero(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name = "ClassicWorldZero.dat";
        const std::filesystem::path inputFile = util::INPUT_FOLDER / "classic" / "c0.0.11a" / "worlds" / name;

        if (!std::filesystem::exists(inputFile)) {
            throw std::runtime_error("Input file does not exist: " + std::string(inputFile));
        }

        logger << inputFile << std::endl;

        std::ifstream strm(inputFile, std::ios::binary);
        zlib::izlibstream zstrm(strm);

        const auto *inputIo = conversion::registry::LevelIORegistry::getInstance().getAs<const minecraft::java::classic::minev1::MineV1LevelIO>(minecraft::java::identifiers::MINEV1_LEVEL_IO);

        auto lvl = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonReadOptions{
            conversion::io::options::fs::file::FileReaderOptions{
                zstrm
            },
            conversion::io::options::versioned::VersionedOptions{
                minecraft::java::Version::rd161348
            }
        });

        const conversion::registry::LevelIORegistry &r = conversion::registry::LevelIORegistry::getInstance();

        const auto io = r.getAs<const minecraft::java::indev::McLevelLevelIO>(
                minecraft::java::identifiers::MCLEVEL_LEVEL_IO);
        const std::filesystem::path outputFolder = util::OUTPUT_FOLDER / "converted" / "indev" / "in-20100223" / "worlds";

        std::filesystem::create_directories(outputFolder);
        std::ofstream ofstrm(outputFolder / name, std::ios::binary);

        io->write(lvl.get(), lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions {
                      conversion::io::options::fs::file::FileWriterOptions {
                          ofstrm
                      },
                      conversion::io::options::versioned::VersionedOptions {
                          minecraft::java::in20100219
                      }
                  });

        return tfw::test::result::TestResult(true, lvl->toString());
    }
}
