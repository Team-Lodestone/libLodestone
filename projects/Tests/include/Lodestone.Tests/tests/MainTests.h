//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MAINTESTS_H
#define LODESTONE_MAINTESTS_H
#include "test/Test.h"

namespace lodestone::tests::test {
    class MainTests : public Test {
    public:
        static void run();

        static void readMcrChunk();
        static void readMcrFile();
    };
}

#endif //LODESTONE_MAINTESTS_H
