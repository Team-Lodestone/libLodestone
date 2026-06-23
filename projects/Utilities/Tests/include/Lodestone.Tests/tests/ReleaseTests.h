//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_RELEASETESTS_H
#define LODESTONE_RELEASETESTS_H
#include "Lodestone.Tests/test/Test.h"

#include <TestFramework/TestFramework.h>

namespace lodestone::tests::test {
    class ReleaseTests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readSnowReleaseWorldZero(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_RELEASETESTS_H
