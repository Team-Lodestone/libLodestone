//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONCHUNKINFO_H
#define LODESTONE_REGIONCHUNKINFO_H

namespace lodestone::minecraft::common::region {
    struct RegionChunkIndice {
        uint32_t offset;
        uint8_t size;
        int32_t timestamp;
    };
} // namespace lodestone::minecraft::common::region

#endif // LODESTONE_REGIONCHUNKINFO_H