//
// Created by DexrnZacAttack on 11/23/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunkIo.h"
#include <libnbt++/nbt_tags.h>

#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunk.h"
#include "Lodestone.Minecraft.Java/mcr/chunk/McRegionChunk.h"
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/data/ExtendedNumericBlockData.h>

namespace lodestone::minecraft::java::anvil::jungle::chunk {
    std::unique_ptr<level::chunk::Chunk>
    JungleAnvilChunkIO::read(nbt::tag_compound &chunk,
                             const int version) const {
        const int32_t x = chunk["xPos"].get().as<nbt::tag_int>().get();
        const int32_t z = chunk["zPos"].get().as<nbt::tag_int>().get();
        const int64_t lastUpdate =
            chunk["LastUpdate"].get().as<nbt::tag_long>().get();
        const nbt::tag_list sections =
            chunk["Sections"].get().as<nbt::tag_list>();

        std::unique_ptr<JungleAnvilChunk> c =
            std::make_unique<JungleAnvilChunk>(level::types::Vec2i(x, z),
                                               lastUpdate);

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            io = LodestoneJava::getInstance()->io.getIo(version);

        for (auto &s : sections) {
            nbt::tag_compound section = s.as<nbt::tag_compound>();
            const int8_t *blocks =
                section["Blocks"].get().as<nbt::tag_byte_array>().get().data();
            const int8_t *data =
                section["Data"].get().as<nbt::tag_byte_array>().get().data();
            const int8_t *add = nullptr;

            if (section.has_key("Add"))
                add =
                    section["Add"].get().as<nbt::tag_byte_array>().get().data();

            const int8_t sy = section["Y"].get().as<nbt::tag_byte>();
            const int lsy = sy * 16;
            // TODO lighting and entities

            for (int cy = 0; cy < 16; cy++) {
                for (int cz = 0; cz < CHUNK_DEPTH; cz++) {
                    for (int cx = 0; cx < CHUNK_WIDTH; cx++) {
                        const size_t idx =
                            INDEX_YZX(cx, cy, cz, CHUNK_WIDTH, CHUNK_DEPTH);

                        uint16_t bb = blocks[idx];

                        if (add)
                            bb += GET_NIBBLE(add, idx) << 8;

#ifdef USE_RISKY_OPTIMIZATIONS
                        if (bb == 0)  // since air is id 0
                            continue; // this skips us having to convert the
                                      // block
#endif

                        const uint8_t d = GET_NIBBLE(data, idx);

                        level::block::properties::BlockProperties b =
                            io->convertBlockToInternal(
                                lodestone::conversion::block::data::
                                    ExtendedNumericBlockData(
                                        bb,
                                        0)); // TODO metadata (maybe MetadataIO
                                             // or
                        // BlockPropertyIO?)

                        if (b.getBlock() !=
                            level::block::BlockRegistry::sDefaultBlock)
                            c->JungleAnvilChunk::setBlock(std::move(b), cx,
                                                          lsy + cy, cz);
                    }
                }
            }
        }

        return c;
    }

    nbt::tag_compound
    JungleAnvilChunkIO::write(level::chunk::Chunk *c,
                              const level::types::Vec2i &coords,
                              int version) const {
        // TODO!
    }

    size_t JungleAnvilChunkIO::getSize(level::chunk::Chunk *c,
                                       int version) const {
        return 0;
    }

    std::unique_ptr<lodestone::level::chunk::Chunk>
    JungleAnvilChunkIO::read(std::istream &in, const int version) const {
        nbt::io::stream_reader streamReader =
            nbt::io::stream_reader(in, endian::big);

        auto [name, root] = streamReader.read_compound();
        nbt::tag_compound &level =
            (root.get()->at("Level").as<nbt::tag_compound>());
        return read(level, version);
    }

    void JungleAnvilChunkIO::write(lodestone::level::chunk::Chunk *c,
                                   const level::types::Vec2i &coords,
                                   int version, std::ostream &out) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(out, endian::big);

        w.write_tag("", write(c, coords, version));
    }
} // namespace lodestone::minecraft::java::anvil::jungle::chunk
