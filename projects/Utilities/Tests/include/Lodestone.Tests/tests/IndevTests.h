//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_INDEVTESTS_H
#define LODESTONE_INDEVTESTS_H
#include "Lodestone.Tests/test/Test.h"
#include <TestFramework/TestFramework.h>

namespace lodestone::tests::test {
    class IndevTests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readHugeFloatingWorld(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_INDEVTESTS_H
