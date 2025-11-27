//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MAINTESTS_H
#define LODESTONE_MAINTESTS_H
#include "Lodestone.Tests/test/Test.h"

namespace lodestone::tests::test {
    class MainTests : public Test {
      public:
        static void run();

        static void readAnvilWorld();

        static void readMcrChunk();

        static void readMcrFile();

        static void readMcrWorld();

        static void readMinev2World();

        static void readAlphaWorld();

        static void writeAlphaWorld();
    };
} // namespace lodestone::tests::test

#endif // LODESTONE_MAINTESTS_H