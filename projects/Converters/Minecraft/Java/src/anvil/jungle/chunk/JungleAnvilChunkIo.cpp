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

    void
    JungleAnvilNbtChunkIO::write(level::chunk::Chunk *chunk,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const common::conversion::io::options::OptionPresets::CommonChunkOptions> &options) const {
        nbt::tag_compound root, level;

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            bio = LodestoneJava::getInstance()->io.getIo(options.version);

        constexpr int sectionSize3D = JungleAnvilChunkIO::CHUNK_WIDTH * JungleAnvilChunkIO::SECTION_HEIGHT * JungleAnvilChunkIO::CHUNK_DEPTH;
        constexpr int sectionSize2D = JungleAnvilChunkIO::CHUNK_WIDTH * JungleAnvilChunkIO::CHUNK_DEPTH;

        // todo make sure to not write EmptyChunk
        level["xPos"] = nbt::tag_int(options.coords.x);
        level["zPos"] = nbt::tag_int(options.coords.y);
        level["LastUpdate"] = nbt::tag_long(0); // TODO
        level["TerrainPopulated"] = nbt::tag_byte(true);

        // todo wiki says there's tileticks which is gonna be pain
        std::vector<int32_t> heightMap(sectionSize2D);

        // todo does new vector preinit?
        std::vector<int8_t> biomes(sectionSize2D); // TODO biomes
        std::fill_n(biomes.data(), sectionSize2D, -1);

        nbt::tag_list sections;
        sections.reserve(chunk->getSectionCount());

        for (int sy = 0; sy < chunk->getSectionCount(); sy++) {
            nbt::tag_compound section;

            // TODO if we ever add floor field to chunk we need to fix these
            level::chunk::section::Section *s = chunk->getSection(sy);

            std::vector<int8_t> blocks(sectionSize3D);
            std::vector<int8_t> data(sectionSize3D / 2);
            std::vector<int8_t> skyLight(sectionSize3D / 2);
            std::vector<int8_t> blockLight(sectionSize3D / 2);
            // TODO we can implement Add (extended block ids) later too

            if (s) {
                for (int cy = 0; cy < JungleAnvilChunkIO::SECTION_HEIGHT; cy++) {
                    for (int cz = 0; cz < JungleAnvilChunkIO::CHUNK_DEPTH; cz++) {
                        for (int cx = 0; cx < JungleAnvilChunkIO::CHUNK_WIDTH; cx++) {
                            const size_t idx =
                                INDEX_YZX(cx, cy, cz, JungleAnvilChunkIO::CHUNK_WIDTH, JungleAnvilChunkIO::CHUNK_DEPTH);
                            const level::block::instance::BlockInstance &b =
                                s->getBlock(cx, cy, cz);

#                           ifdef USE_RISKY_OPTIMIZATIONS
                            if (b.getBlock() !=
                                level::block::BlockRegistry::s_defaultBlock) {
#                           endif
                                uint8_t id = 0;
                                uint8_t dat = 0;

                                if (const lodestone::conversion::block::data::ExtendedNumericBlockData *bl =
                                            bio->convertBlockFromInternal(&b)->as<lodestone::conversion::block::data::ExtendedNumericBlockData>()) {
                                    id = bl->getId();
                                    dat = bl->getData();
                                            }

                                blocks[idx] = id;

                                SET_NIBBLE(data, idx, dat);
#ifdef USE_RISKY_OPTIMIZATIONS
                                }
#endif

                            SET_NIBBLE(skyLight, idx,
                                       s ? s->getSkyLight()->getNibble(cx, cy, cz)
                                         : 15);
                            SET_NIBBLE(
                                blockLight, idx,
                                s ? s->getBlockLight()->getNibble(cx, cy, cz)
                                  : 15);
                        }
                    }
                }
            }

            section["Y"] = nbt::tag_byte(sy);
            section["Blocks"] = nbt::tag_byte_array(std::move(blocks));
            section["Data"] = nbt::tag_byte_array(std::move(data));
            section["BlockLight"] = nbt::tag_byte_array(std::move(blockLight));
            section["SkyLight"] = nbt::tag_byte_array(std::move(skyLight));

            sections.push_back(std::move(section));
        }

        for (int cz = 0; cz < JungleAnvilChunkIO::CHUNK_DEPTH; cz++) {
            for (int cx = 0; cx < JungleAnvilChunkIO::CHUNK_WIDTH; cx++) {
                heightMap[INDEX_YX(cx, cz, JungleAnvilChunkIO::CHUNK_WIDTH)] = chunk->getHeightAt(cx, cz);
            }
        }

        level["Sections"] = std::move(sections);
        level["HeightMap"] = nbt::tag_int_array(std::move(heightMap));
        level["Biomes"] = nbt::tag_byte_array(std::move(biomes));

        // TODO entities
        level["Entities"] = nbt::tag_list();     // TODO
        level["TileEntities"] = nbt::tag_list(); // TODO

        root["Level"] = std::move(level);

        options.output = root;
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
