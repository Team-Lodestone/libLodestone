//
// Created by zero on 6/4/26.
//

#include "Lodestone.Tests/tests/PreclassicTests.h"

#include <filesystem>
#include <TestFramework/TestFramework.h>

#include <libnbt++/io/izlibstream.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Java/Identifiers.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/conversion/classic/minev1/MineV1LevelIO.h>
#include "Lodestone.Tests/util.h"

namespace lodestone::tests::test {
    void PreclassicTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_PRECLASSIC_WORLD_ZERO, "Read Preclassic World (Zero)", readPreclassicWorldZero);
    }

    tfw::test::result::TestResult PreclassicTests::readPreclassicWorldZero(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name = "PreclassicWorldZero.dat";
        const std::filesystem::path inputFile = util::INPUT_FOLDER / "preclassic" / "rd-132211" / "worlds" / name;

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
                minecraft::java::Version::rd131655
            }
        });

        return tfw::test::result::TestResult(true, lvl->toString());
    }
}
