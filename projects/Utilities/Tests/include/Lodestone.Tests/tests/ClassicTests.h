//
// Created by zero on 6/4/26.
//

#ifndef LODESTONE_CLASSICTESTS_H
#define LODESTONE_CLASSICTESTS_H
#include <TestFramework/TestFramework.h>
#include "Lodestone.Tests/test/Test.h"


namespace lodestone::tests::test {
    class ClassicTests : public Test {
    public:
        static void add();

        static tfw::test::result::TestResult readClassicWorldZero(tfw::test::logging::loggers::ITestLogger &logger);
    };
} // lodestone::tests::test

#endif //LODESTONE_CLASSICTESTS_H
