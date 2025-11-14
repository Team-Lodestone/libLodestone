//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNKIO_H
#define LODESTONE_MCREGIONCHUNKIO_H
#include <libnbt++/tag_compound.h>
#include <Lodestone.Conversion/chunk/ChunkIO.h>

namespace lodestone::java::mcr::chunk {
    class McRegionChunkIO : public lodestone::conversion::chunk::ChunkIO {
    public:
        std::unique_ptr<level::chunk::Chunk> read(uint8_t *data, size_t size, int version) const override;

        std::unique_ptr<level::chunk::Chunk> read(nbt::tag_compound &chunk, int version) const;

        uint8_t *write(level::chunk::Chunk *c, int version) const override;

        nbt::tag_compound write(level::chunk::Chunk &c) const;

        size_t getSize(level::chunk::Chunk *c, int version) const override;
    };
}

#endif //LODESTONE_MCREGIONCHUNKIO_H
