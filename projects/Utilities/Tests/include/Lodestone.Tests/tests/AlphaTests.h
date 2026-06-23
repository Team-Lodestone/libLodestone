//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_ALPHATESTS_H
#define LODESTONE_ALPHATESTS_H

#include "Lodestone.Tests/test/Test.h"
#include <TestFramework/TestFramework.h>

namespace lodestone::tests::test {
    class AlphaTests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readSnowWorldZero(tfw::test::logging::loggers::ITestLogger &logger);
        static tfw::test::result::TestResult readNetherWorldZero(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_ALPHATESTS_H
