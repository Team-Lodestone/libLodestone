//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_BETATESTS_H
#define LODESTONE_BETATESTS_H

#include <TestFramework/TestFramework.h>

#include "Lodestone.Tests/test/Test.h"

namespace lodestone::tests::test {
    class BetaTests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readBetaServerWorld(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_BETATESTS_H
