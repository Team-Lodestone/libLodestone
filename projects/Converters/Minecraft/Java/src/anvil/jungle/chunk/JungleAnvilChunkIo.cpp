//
// Created by DexrnZacAttack on 11/23/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"
#include <libnbt++/nbt_tags.h>

#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilChunk.h"
#include "Lodestone.Minecraft.Java/mcregion/McRegionChunk.h"
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/data/ExtendedNumericBlockData.h>

namespace lodestone::minecraft::java::anvil::jungle::chunk {
    std::unique_ptr<level::chunk::Chunk>
    JungleAnvilNbtChunkIO::read(const common::conversion::io::options::OptionPresets::CommonNbtReadOptions &options) const {
        const int32_t x = options.input["xPos"].get().as<nbt::tag_int>().get();
        const int32_t z = options.input["zPos"].get().as<nbt::tag_int>().get();
        const int64_t lastUpdate =
            options.input["LastUpdate"].get().as<nbt::tag_long>().get();
        const nbt::tag_list sections =
            options.input["Sections"].get().as<nbt::tag_list>();

        std::unique_ptr<JungleAnvilChunk> c =
            std::make_unique<JungleAnvilChunk>(level::types::Vec2i(x, z),
                                               lastUpdate);

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            io = LodestoneJava::getInstance()->io.getIo(options.version);

        for (auto &s : sections) {
            nbt::tag_compound section = s.as<nbt::tag_compound>();
            const int8_t *blocks =
                section["Blocks"].get().as<nbt::tag_byte_array>().get().data();
            const int8_t *data =
                section["Data"].get().as<nbt::tag_byte_array>().get().data();
            const int8_t *add = nullptr;

            // todo handle when lighting doesn't exist
            const int8_t *skyLight = section["SkyLight"]
                                         .get()
                                         .as<nbt::tag_byte_array>()
                                         .get()
                                         .data();
            const int8_t *blockLight = section["BlockLight"]
                                           .get()
                                           .as<nbt::tag_byte_array>()
                                           .get()
                                           .data();

            if (section.has_key("Add"))
                add =
                    section["Add"].get().as<nbt::tag_byte_array>().get().data();

            const int8_t sy = section["Y"].get().as<nbt::tag_byte>();
            const int lsy = sy * JungleAnvilChunkIO::SECTION_HEIGHT;

            // TODO lighting and entities
            for (int cy = 0; cy < JungleAnvilChunkIO::SECTION_HEIGHT; cy++) {
                for (int cz = 0; cz < JungleAnvilChunkIO::CHUNK_DEPTH; cz++) {
                    for (int cx = 0; cx < JungleAnvilChunkIO::CHUNK_WIDTH; cx++) {
                        const size_t idx =
                            INDEX_YZX(cx, cy, cz, JungleAnvilChunkIO::CHUNK_WIDTH, JungleAnvilChunkIO::CHUNK_DEPTH);

                        uint16_t bb = blocks[idx];

                        if (add)
                            bb += GET_NIBBLE(add, idx) << 8;

#ifdef USE_RISKY_OPTIMIZATIONS
                        if (bb == 0)  // since air is id 0
                            continue; // this skips us having to convert the
                                      // block
#endif

                        const uint8_t d = GET_NIBBLE(data, idx);

                        level::block::instance::BlockInstance b =
                            io->convertBlockToInternal(
                                lodestone::conversion::block::data::
                                    ExtendedNumericBlockData(
                                        bb,
                                        0)); // TODO metadata (maybe MetadataIO
                                             // or
                        // BlockPropertyIO

                        if (b.getBlock() !=
                            level::block::BlockRegistry::s_defaultBlock) {
                            c->JungleAnvilChunk::setBlock(std::move(b), cx,
                                                          lsy + cy, cz);
                        }

                        if (level::chunk::section::Section *sec =
                                c->getSection(cy >> 4)) {
                            sec->getBlockLight()->setNibble(
                                cx, cy, cz, GET_NIBBLE(skyLight, idx));
                            sec->getSkyLight()->setNibble(
                                cx, cy, cz, GET_NIBBLE(blockLight, idx));
                        }
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

    std::unique_ptr<lodestone::level::chunk::Chunk>
    JungleAnvilChunkIO::read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const {
        auto streamReader = nbt::io::stream_reader(options.input, endian::big);

        auto [name, root] = streamReader.read_compound();
        nbt::tag_compound &level =
            root.get()->at("Level").as<nbt::tag_compound>();

        const JungleAnvilNbtChunkIO *io = this->getAsByRelation<const JungleAnvilNbtChunkIO, &identifiers::NBT_CHUNK_IO>();
        return io->read(common::conversion::io::options::OptionPresets::CommonNbtReadOptions {
            common::conversion::io::options::NbtReaderOptions {
                level,
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        });
    }

    void JungleAnvilChunkIO::write(level::chunk::Chunk *chunk, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(options.output, endian::big);

        const JungleAnvilNbtChunkIO *io = this->getAsByRelation<const JungleAnvilNbtChunkIO, &identifiers::NBT_CHUNK_IO>();
        io->writeToNbtStreamWriter(chunk, "", w, common::conversion::io::options::OptionPresets::CommonChunkOptions {
            common::conversion::io::options::ChunkOptions {
                options.coords
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        });
    }
} // namespace lodestone::minecraft::java::anvil::jungle::chunk
