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

        static tfw::test::result::TestResult generateWaterChunk(tfw::test::util::TestOutputLogger &logger);

        static tfw::test::result::TestResult readAnvilWorld(tfw::test::util::TestOutputLogger &logger);


        static void readMcrChunk(tfw::test::util::TestOutputLogger &logger);

        static void readMcrFile(tfw::test::util::TestOutputLogger &logger);

        static void readMcrWorld(tfw::test::util::TestOutputLogger &logger);

        static void readMinev2World(tfw::test::util::TestOutputLogger &logger);

        static void readAlphaWorld(tfw::test::util::TestOutputLogger &logger);

        static void writeAlphaWorld(tfw::test::util::TestOutputLogger &logger);
    };
} // namespace lodestone::tests::test

#endif // LODESTONE_MAINTESTS_H