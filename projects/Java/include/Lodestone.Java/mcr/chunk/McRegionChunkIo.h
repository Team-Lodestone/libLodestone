//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNKIO_H
#define LODESTONE_MCREGIONCHUNKIO_H
#include <libnbt++/tag_compound.h>
#include <Lodestone.Level/conversion/chunk/ChunkIO.h>

namespace lodestone::java::mcr::chunk {
    class McRegionChunkIO : public level::conversion::chunk::ChunkIO {
    public:
        level::chunk::Chunk *read(uint8_t *data, size_t size, int version) const override;

        level::chunk::Chunk *read(nbt::tag_compound &chunk, int version) const;

        uint8_t *write(level::chunk::Chunk *c, int version) const override;

        nbt::tag_compound write(level::chunk::Chunk &c) const;

        size_t getSize(level::chunk::Chunk *c, int version) const override;
    };
}

#endif //LODESTONE_MCREGIONCHUNKIO_H
