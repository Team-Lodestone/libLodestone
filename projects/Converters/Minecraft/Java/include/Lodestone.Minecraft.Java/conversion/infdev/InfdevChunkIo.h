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
#include <memory>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Level/chunk/Chunk.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>

namespace lodestone::minecraft::java::infdev::chunk {
    class InfdevChunkIO : public conversion::io::ChunkIO<&identifiers::INF_624_CHUNK_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>
    {
    public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_DEPTH = 16;
        static constexpr int CHUNK_HEIGHT = 128;

        std::unique_ptr<level::chunk::Chunk> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(level::chunk::Chunk *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const override;
    };
}

#endif //LODESTONE_INFDEVCHUNKIO_H
