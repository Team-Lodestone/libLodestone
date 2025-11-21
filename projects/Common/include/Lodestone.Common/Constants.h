//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CONSTANTS_H
#define LODESTONE_CONSTANTS_H

// Shared constants to prevent circular include (e.g. section includes chunk for
// its constants and then chunk needs to include Section)
namespace lodestone::common::constants {
    static constexpr int CHUNK_WIDTH = 16;
    static constexpr int SECTION_HEIGHT = 16;
    static constexpr int CHUNK_DEPTH = 16;
} // namespace lodestone::common::constants

#endif //  LODESTONE_CONSTANTS_H