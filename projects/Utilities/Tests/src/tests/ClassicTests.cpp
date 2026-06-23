//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/ClassicTests.h"

#include <libnbt++/io/izlibstream.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Java/Identifiers.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <TestFramework/TestFramework.h>

#include <Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2LevelIO.h>
#include "Lodestone.Tests/util.h"

namespace lodestone::tests::test {
    void ClassicTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_CLASSIC_WORLD_ZERO, "Read Classic World (Zero)", readClassicWorldZero);
    }

    tfw::test::result::TestResult ClassicTests::readClassicWorldZero(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name = "ClassicWorldZero.dat";
        const std::filesystem::path inputFile = util::INPUT_FOLDER / "classic" / "c0.0.11a" / "worlds" / name;

        if (!std::filesystem::exists(inputFile)) {
            throw std::runtime_error("Input file does not exist: " + std::string(inputFile));
        }

        logger << inputFile << std::endl;

        std::ifstream strm(inputFile, std::ios::binary);
        zlib::izlibstream zstrm(strm);

        const auto *inputIo = conversion::registry::LevelIORegistry::getInstance().getAs<const minecraft::java::classic::minev2::MineV2LevelIO>(minecraft::java::identifiers::MINEV2_LEVEL_IO);

        auto lvl = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonReadOptions{
            conversion::io::options::fs::file::FileReaderOptions{
                zstrm
            },
            conversion::io::options::versioned::VersionedOptions{
                minecraft::java::Version::rd161348
            }
        });

        return tfw::test::result::TestResult(true, lvl->toString());
    }
}
