//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_PRECLASSICTESTS_H
#define LODESTONE_PRECLASSICTESTS_H
#include "Lodestone.Tests/test/Test.h"

#include <TestFramework/TestFramework.h>

namespace lodestone::tests::test {
    class PreclassicTests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readPreclassicWorldZero(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_PRECLASSICTESTS_H
