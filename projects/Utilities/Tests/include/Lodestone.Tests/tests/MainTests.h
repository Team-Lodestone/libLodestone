//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MAINTESTS_H
#define LODESTONE_MAINTESTS_H
#include "Lodestone.Tests/test/Test.h"
#include <TestFramework/TestFramework.h>

namespace lodestone::tests::test {
    class MainTests : public Test {
      public:
        static void add();

        static tfw::test::result::TestResult generateWaterChunk(tfw::test::logging::loggers::ITestLogger &logger);

        static tfw::test::result::TestResult readAnvilWorld(tfw::test::logging::loggers::ITestLogger &logger);

        static tfw::test::result::TestResult writeAnvilWorld(tfw::test::logging::loggers::ITestLogger &logger);

        static void readMcrChunk(tfw::test::logging::loggers::ITestLogger &logger);

        static void readMcrFile(tfw::test::logging::loggers::ITestLogger &logger);

        static void readMcrWorld(tfw::test::logging::loggers::ITestLogger &logger);

        static void readMinev2World(tfw::test::logging::loggers::ITestLogger &logger);

        static void readAlphaWorld(tfw::test::logging::loggers::ITestLogger &logger);

        static void writeAlphaWorld(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // namespace lodestone::tests::test

#endif // LODESTONE_MAINTESTS_H