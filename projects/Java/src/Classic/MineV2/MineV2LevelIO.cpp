//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Classic/MineV2/MineV2LevelIO.h"

#include "BinaryIO.h"
#include "Classic/ClassicBlockIO.h"
#include "Classic/MineV1/MineV1LevelIO.h"

namespace lodestone::java::classic::minev2 {
    level::Level * MineV2LevelIO::read(uint8_t *data) const {
        level::Level *l = new level::Level();
        bio::BinaryIO io(data);

        // TODO: MOVE TO WORLD IO WHEN FINISHED, THIS IS WORLD INFO
        io.readBE<uint32_t>();
        io.readSignedByte();
        io.readString(io.readBE<uint16_t>());
        io.readString(io.readBE<uint16_t>());
        io.readBE<uint64_t>();
        // ENDMOVE

        const int width = io.readBE<uint16_t>();
        const int depth = io.readBE<uint16_t>();
        const int height = io.readBE<uint16_t>();

        uint8_t *rd = io.getDataRelative();
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                for (int x = 0; x < width; x++) {
                    level::block::state::BlockState b = ClassicBlockIO::sInstance->readBlock(rd);
                    if (b.getBlock() != level::block::BlockRegistry::sDefaultBlock)
                        l->setBlockCreateRaw(b, x, y, z, height);

                    rd++;
                }
            }
        }

        for (auto &[coords, chunk] : l->getChunks())
            chunk->calculateHeightmap();

        return l;
    }

    uint8_t * MineV2LevelIO::write(level::Level *l) const {
        bio::BinaryIO io(new uint8_t[getSize(l)]);

        auto [min, max] = l->getBlockBounds();

        const int w = (max.x - min.x + 1);
        const int h = (max.y - min.y);
        const int d = (max.z - min.z + 1);

        io.writeBE<uint16_t>(w);
        io.writeBE<uint16_t>(d);
        io.writeBE<uint16_t>(h);

        for (int y = 0; y < h; y++) {
            for (int z = 0; z < d; z++) {
                for (int x = 0; x < w; x++) {
                    level::block::state::BlockState *b = l->getBlock(x, y, z);
                    if (b->getBlock() != level::block::BlockRegistry::sDefaultBlock)
                        ClassicBlockIO::sInstance->writeBlock(b, io.getDataRelative());

                    io.seekRelative(1); // TODO: I can make this operator++
                }
            }
        }

        return io.getData();
    }

    size_t MineV2LevelIO::getSize(level::Level *l) const {
        return 2 + 2 + 2 + l->getBlockCount();
    }
}
