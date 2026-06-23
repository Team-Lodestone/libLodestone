//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_INFDEV624TESTS_H
#define LODESTONE_INFDEV624TESTS_H
#include <TestFramework/test/result/TestResult.h>
#include "Lodestone.Tests/test/Test.h"
#include <TestFramework/test/logging/loggers/ITestLogger.h>

namespace lodestone::tests::test {
    class Infdev624Tests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readWorld4(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_INFDEV624TESTS_H
