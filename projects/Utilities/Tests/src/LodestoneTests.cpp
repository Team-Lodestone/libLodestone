//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

#include <filesystem>
#include <iostream>
#include <ostream>
#include <print>
#include <BinaryIO/Exports.h>
#include <Lodestone.Common/LodestoneCommon.h>
#include <Lodestone.Core/loader/NativeExtensionLoader.h>
#include <Lodestone.Level/chunk/Chunk.h>
#include <Lodestone.Minecraft.Java/LodestoneJava.h>

#include "Lodestone.Tests/util.h"
#include "Lodestone.Tests/tests/AlphaTests.h"
#include "Lodestone.Tests/tests/BetaTests.h"
#include "Lodestone.Tests/tests/ClassicTests.h"
#include "Lodestone.Tests/tests/IndevTests.h"
#include "Lodestone.Tests/tests/Infdev624Tests.h"
#include "Lodestone.Tests/tests/InfdevTests.h"
#include "Lodestone.Tests/tests/PreclassicTests.h"
#include "Lodestone.Tests/tests/ReleaseTests.h"

int main(const int argc, char **argv) {
    LOG_INFO(lodestone::common::lodestone_get_library_string());
    LOG_INFO(bio::bio_get_library_string());

    lodestone::core::loader::NativeExtensionLoader l("./extensions", lodestone::core::Lodestone::getInstance());
    l.extensionLoadedEvent += [](const lodestone::core::LodestoneExtension *ext) {
        std::print("Initialized extension '{}' {}\n", ext->getIdentifier(), ext->getVersion().toString());
    };

    l.loadExtension(lodestone::minecraft::java::lodestoneInit);

    std::filesystem::create_directories(lodestone::tests::util::INPUT_FOLDER);
    std::filesystem::create_directories(lodestone::tests::util::OUTPUT_FOLDER);

    const auto tfw = tfw::TestFramework::initFromArgs(argc, argv);

    ADD_TESTS(RUN_PRECLASSIC_TESTS, lodestone::tests::test::PreclassicTests::add);
    ADD_TESTS(RUN_CLASSIC_TESTS, lodestone::tests::test::ClassicTests::add);
    ADD_TESTS(RUN_INDEV_TESTS, lodestone::tests::test::IndevTests::add);
    ADD_TESTS(RUN_INFDEV_TESTS, lodestone::tests::test::InfdevTests::add);
    ADD_TESTS(RUN_INFDEV624_TESTS, lodestone::tests::test::Infdev624Tests::add);
    ADD_TESTS(RUN_ALPHA_TESTS, lodestone::tests::test::AlphaTests::add);
    ADD_TESTS(RUN_BETA_TESTS, lodestone::tests::test::BetaTests::add);
    ADD_TESTS(RUN_RELEASE_TESTS, lodestone::tests::test::ReleaseTests::add);

    tfw->run();

    return 0;
};