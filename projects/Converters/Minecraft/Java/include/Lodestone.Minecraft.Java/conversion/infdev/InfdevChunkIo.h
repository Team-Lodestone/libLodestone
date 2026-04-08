/** @file InfdevChunkIo.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVCHUNKIO_H
#define LODESTONE_INFDEVCHUNKIO_H
#include <BinaryIO/io/Serializable.h>

#include <memory>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Level/chunk/Chunk.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>

namespace lodestone::minecraft::java::infdev::chunk {
    class InfdevChunkIO : public conversion::io::ChunkIO<&identifiers::INF_624_CHUNK_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>
    {
    public:
        struct Properties {
            using Deserializer = bio::io::Deserializable<Properties, void>;
            using Serializer = bio::io::Serializable<Properties, void>;

            const bool terrainPopulated;

            constexpr int64_t serialize() const {
                return 0
                    | (this->terrainPopulated ? 0b0000000000000001 : 0L);
            }

            constexpr static Properties fromSerialized(const int64_t value) {
                return {
                    .terrainPopulated = (value & 0b0000000000000001) == 1
                };
            }
        };

        std::unique_ptr<level::chunk::Chunk> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(level::chunk::Chunk *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const override;
    };
}

using namespace lodestone::minecraft::java::infdev::chunk;

template <>
class bio::io::Deserializable<InfdevChunkIO::Properties, void> {
public:
    using Type = InfdevChunkIO::Properties;
    using Options = void;

    static std::unique_ptr<InfdevChunkIO::Properties> deserialize(ReadableBufferLike auto &readable) {
        const int64_t props = readable.template readBE<int64_t>();
        return std::make_unique<InfdevChunkIO::Properties>(InfdevChunkIO::Properties::fromSerialized(props));
    }
};

template<>
class bio::io::Serializable<InfdevChunkIO::Properties, void> {
public:
    using Type = InfdevChunkIO::Properties;
    using Options = void; // allows us to call serialize without an options arg.

    static void serialize(const InfdevChunkIO::Properties& properties, WritableBufferLike auto &writable) {
        writable.template writeBE<int64_t>(properties.serialize());
    }
};

#endif //LODESTONE_INFDEVCHUNKIO_H
