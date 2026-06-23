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

#include "Lodestone.Tests/util.h"

namespace lodestone::tests::test {
    void IndevTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(READ_INDEV_HUGE_FLOATING, "Read Indev Huge Floating World (Zero)", readHugeFloatingWorld);
    }

    tfw::test::result::TestResult IndevTests::readHugeFloatingWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name = "huge_floating.mclevel";
        const std::filesystem::path inputFile = util::INPUT_FOLDER / "indev" / "in-20100223" / "worlds" / name;

        logger << inputFile << std::endl;

        std::ifstream strm(inputFile, std::ios::binary);
        zlib::izlibstream zstrm(strm);

        const auto *inputIo = conversion::registry::LevelIORegistry::getInstance().getAs<const
            minecraft::java::indev::McLevelLevelIO>(minecraft::java::identifiers::MCLEVEL_LEVEL_IO);

        auto lvl = inputIo->read(minecraft::common::conversion::io::options::OptionPresets::CommonReadOptions{
            conversion::io::options::fs::file::FileReaderOptions{
                zstrm
            },
            conversion::io::options::versioned::VersionedOptions{
                minecraft::java::Version::in20100219
            }
        });

        return tfw::test::result::TestResult(true, lvl->toString());
    }
}
