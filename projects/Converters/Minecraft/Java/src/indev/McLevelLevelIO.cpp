//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//

#include "Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIO.h"

#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>

#include <libnbt++/io/ozlibstream.h>
#include "Lodestone.Level/world/World.h"
#include "Lodestone.Minecraft.Java/LodestoneJava.h"

namespace lodestone::minecraft::java::indev {

    std::unique_ptr<level::Level>
    McLevelLevelIO::read(
        const common::conversion::io::options::OptionPresets::CommonReadOptions
        &options) const {
        auto streamReader = nbt::io::stream_reader(options.input, endian::big);

        auto [name, root] = streamReader.read_compound();

        const McLevelNbtLevelIO *io = this->getAsByRelation<
            const McLevelNbtLevelIO, &identifiers::NBT_LEVEL_IO>();

        return io->read(
            common::conversion::io::options::OptionPresets::CommonNbtReadOptions
            {
                common::conversion::io::options::NbtReaderOptions{
                    *root.get()
                },
                conversion::io::options::versioned::VersionedOptions{
                    options.version
                }
            });
    }

    void McLevelLevelIO::write(level::Level *l,
                               const
                               common::conversion::io::options::OptionPresets::CommonWriteOptions
                               &options) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(options.output, endian::big);

        const McLevelNbtLevelIO *io = this->getAsByRelation<const McLevelNbtLevelIO, &identifiers::NBT_LEVEL_IO>();
        io->writeToNbtStreamWriter(l, "MinecraftLevel", w, conversion::io::options::versioned::VersionedOptions {
            options.version
        });
    }

    std::unique_ptr<level::Level> McLevelNbtLevelIO::read(
        const common::conversion::io::options::OptionPresets::
        CommonNbtReadOptions &options) const {

        auto lvl = std::make_unique<level::Level>(level::Level());
        auto root = options.input;

        // Environment tag
        auto environment = root["Environment"].get_as<nbt::tag_compound>();
        const int16_t surroundingGroundHeight = environment[
            "SurroundingGroundHeight"].get_as<nbt::tag_short>().get();
        const int16_t timeOfDay = environment["TimeOfDay"].get_as<
            nbt::tag_short>().get();
        const int16_t cloudHeight = environment["CloudHeight"].get_as<
            nbt::tag_short>().get();
        const int32_t cloudColor = environment["CloudColor"].get_as<
            nbt::tag_int>().get();
        const int8_t skyBrightness = environment["SkyBrightness"].get_as<
            nbt::tag_byte>().get();
        const int32_t skyColor = environment["SkyColor"].get_as<nbt::tag_int>().
            get();
        const int32_t fogColor = environment["FogColor"].get_as<nbt::tag_int>().
            get();
        const int16_t surroundingWaterHeight = environment[
            "SurroundingWaterHeight"].get_as<nbt::tag_short>().get();
        const int8_t surroundingGroundType = environment["SurroundingGroundType"].
            get_as<nbt::tag_byte>().get();
        const int8_t surroundingWaterType = environment["SurroundingWaterType"].
            get_as<nbt::tag_byte>().get();

        // Map tag
        auto map = root["Map"].get_as<nbt::tag_compound>();
        const int16_t length = map["Length"].get_as<nbt::tag_short>().get();
        const int16_t width = map["Width"].get_as<nbt::tag_short>().get();
        const int16_t height = map["Height"].get_as<nbt::tag_short>().get();

        const std::vector<int8_t> blocks = map["Blocks"].get_as<
            nbt::tag_byte_array>().get();
        const std::vector<int8_t> data = map["Data"].get_as<
            nbt::tag_byte_array>().get();

        const std::unique_ptr<conversion::block::version::BlockIO> io =
            LodestoneJava::getInstance()->m_blockIo.getIo(options.version);

        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                for (int x = 0; x < width; x++) {
                    const size_t idx = INDEX_YZX(x, y, z, width, length);

                    const uint8_t bb = blocks[idx];

#ifdef USE_RISKY_OPTIMIZATIONS
                    if (bb == 0) // since air is id 0
                        continue; // this skips us having to convert the block
#endif

                    const int8_t metadata = data[idx] & 0x0F;
                    const int8_t lighting = data[idx] & 0xF0;

                    level::block::instance::BlockInstance b =
                        io->convertBlockToInternal(
                            conversion::block::data::
                            NumericBlockData(
                                bb,
                                0));
                    // leave as zero until block states are implemented

                    if (b.getBlock() != level::block::BlockRegistry::s_defaultBlock) {
                        lvl->setBlockCreate(std::move(b), x, y, z, height);
                    }

                    if (level::chunk::Chunk *ch = lvl->getChunk(level::coords::ChunkCoordinates::fromBlockCoordinates(x, z))) {
                        if (level::chunk::section::Section *s = ch->getSectionFromBlockY(y)) {
                            s->setBlockLight(level::coords::ChunkCoordinates::blockToLocalChunkX(x), level::coords::SectionCoordinates::blockToLocalSectionY(y), level::coords::ChunkCoordinates::blockToLocalChunkZ(z), lighting);

                            // TODO its late so don't want to bother with this yet
                            // uint8_t brightness = (skyBrightness * 15);
                            // if (brightness != 0) {
                            //     brightness /= 100;
                            // }
                            //
                            // size_t h = ch->getHeightAt(CHUNK_LOCAL_IDX(x, width), CHUNK_LOCAL_IDX(z, length));
                            //
                            // for (size_t i = height; i > h; i--) {
                            //     ch->setSkyLight(CHUNK_LOCAL_IDX(x, width), i, CHUNK_LOCAL_IDX(z, length), brightness);
                            // }
                        }
                    }
                }
            }
        }

        // TODO: TileEntities tag

        // About tag
        auto about = root["About"].get_as<nbt::tag_compound>();
        const std::string author = about["Author"].get_as<nbt::tag_string>().
            get();
        const int64_t createdOn = about["CreatedOn"].get_as<nbt::tag_long>().
            get();
        lvl->setCreationTime(createdOn);
        const std::string name = about["Name"].get_as<nbt::tag_string>().get();

        // TODO: Entities tag

        return lvl;
    }

    void McLevelNbtLevelIO::write(level::Level *l,
                                  const
                                  common::conversion::io::options::OptionPresets::NbtOutputWriteOptions
                                  <const conversion::io::options::versioned::VersionedOptions>
                                  &options) const {
        auto &root = options.output;

        //region Environment
        auto environment = nbt::tag_compound();

        const auto cloudColor = l->getPropertyOr("CloudColor", 0xFFFFFF);
        const auto cloudHeight = l->getPropertyOr("CloudHeight", static_cast<int16_t>(66));
        const auto fogColor = l->getPropertyOr("FogColor", 0xFFFFFF);
        const auto skyBrightness = l->getPropertyOr("SkyBrightness", static_cast<int8_t>(0xF));
        const auto skyColor = l->getPropertyOr("SkyColor", 0x99CCFF);
        const auto surroundingGroundHeight = l->getPropertyOr("SurroundingGroundHeight", static_cast<int16_t>(2));
        const auto surroundingGroundType = l->getPropertyOr("SurroundingGroundType", static_cast<int8_t>(2));
        const auto surroundingWaterHeight = l->getPropertyOr("SurroundingWaterHeight", static_cast<int16_t>(32));
        const auto surroundingWaterType = l->getPropertyOr("SurroundingWaterType", static_cast<int8_t>(8));
        const auto timeOfDay = l->getPropertyOr("TimeOfDay", static_cast<int16_t>(16));
        environment["CloudColor"] = cloudColor->getValue();
        environment["CloudHeight"] = cloudHeight->getValue();
        environment["FogColor"] = fogColor->getValue();
        environment["SkyBrightness"] = skyBrightness->getValue();
        environment["SkyColor"] = skyColor->getValue();
        environment["SurroundingGroundHeight"] = surroundingGroundHeight->getValue();
        environment["SurroundingGroundType"] = surroundingGroundType->getValue();
        environment["SurroundingWaterHeight"] = surroundingWaterHeight->getValue();
        environment["SurroundingWaterType"] = surroundingWaterType->getValue();
        environment["TimeOfDay"] = timeOfDay->getValue();

        //region Map
        auto map = nbt::tag_compound();

        const auto spawnPos = l->getSpawnPos();
        const auto spawn = nbt::tag_list({
            static_cast<int16_t>(spawnPos.x),
            static_cast<int16_t>(spawnPos.y),
            static_cast<int16_t>(spawnPos.z)
        });
        map.emplace<nbt::tag_list>("Spawn", spawn);

        const auto levelBounds = l->getBlockBounds();
        const auto height = levelBounds.getHeight();
        const auto width = levelBounds.getWidth();
        const auto length = levelBounds.getLength();
        map["Height"] = nbt::tag_short(height);
        map["Width"] = nbt::tag_short(width);
        map["Length"] = nbt::tag_short(length);

        auto blocks = std::vector<int8_t>(height * width * length);
        auto metadata = std::vector<int8_t>(height * width * length);

        const std::unique_ptr<conversion::block::version::BlockIO> bio =
            LodestoneJava::getInstance()->m_blockIo.getIo(options.version);

        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                for (int x = 0; x < width; x++) {
                    const size_t idx = INDEX_YZX(x, y, z, width, length);

                    const auto bb = l->getBlock(x, y, z);

                    if (bb.getBlock() != level::block::BlockRegistry::s_defaultBlock) {
                        uint8_t blockId = 0;
                        uint8_t data = 0;

                        if (const conversion::block::data::NumericBlockData *bl =
                                    bio->convertBlockFromInternal(&bb)->as<conversion::block::data::NumericBlockData>()) {
                            blockId = bl->getId();
                            data = bl->getData();
                        }

                        blocks[idx] = blockId;
                        metadata[idx] = data;
                    }
                }
            }
        }

        map["Blocks"] = nbt::tag_byte_array(std::move(blocks));
        map["Data"] = nbt::tag_byte_array(std::move(metadata));

        //region About
        auto about = nbt::tag_compound();

        const auto author = l->getPropertyOr("Author", "Player");
        const auto createdOn = l->getPropertyOr("CreatedOn", static_cast<int64_t>(0L));
        const auto name = l->getPropertyOr("Name", "A Nice World");
        about["Author"] = author->getValue();
        about["CreatedOn"] = createdOn->getValue();
        about["Name"] = name->getValue();

        // TODO: Write entity data
        auto entities = nbt::tag_list(nbt::tag_type::Compound);

        // TODO: Write tile entity data
        auto tileEntities = nbt::tag_list(nbt::tag_type::Compound);

        root.emplace<nbt::tag_compound>("Environment", environment);
        root.emplace<nbt::tag_compound>("Map", map);
        root.emplace<nbt::tag_compound>("About", about);
        root.emplace<nbt::tag_list>("Entities", entities);
        root.emplace<nbt::tag_list>("TileEntities", tileEntities);
    }

} // namespace lodestone::minecraft::java::indev