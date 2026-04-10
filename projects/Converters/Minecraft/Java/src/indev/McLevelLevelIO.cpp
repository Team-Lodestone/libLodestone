//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//

#include "Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIO.h"

#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>
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
            LodestoneJava::getInstance()->io.getIo(options.version);

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
                                  <const conversion::io::options::EmptyOptions>
                                  &options) const {
    }

} // namespace lodestone::minecraft::java::indev