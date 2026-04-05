/** @file InfdevZoneIo.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVZONEIO_H
#define LODESTONE_INFDEVZONEIO_H
#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>

#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevChunkIo.h"
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::infdev::zone {
    constexpr uint32_t EXPECTED_MAGIC = 0x13737000;
    constexpr uint16_t EXPECTED_VERSION = 0;

    class InfdevZoneIo : public conversion::io::LevelIO<&identifiers::INF_624_ZONE_IO, const
                             common::conversion::io::options::OptionPresets::CommonChunkReadOptions, const
                             common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>,
                         public conversion::registry::RegistryIdentifierRelations<
                             conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::CHUNK_IO, const
                                 chunk::InfdevChunkIO, &identifiers::INF_624_CHUNK_IO,
                                 conversion::registry::ChunkIORegistry>
                         > {
    public:
        std::unique_ptr<level::Level>
        read(const common::conversion::io::options::OptionPresets::CommonChunkReadOptions &options) const override;

        void write(level::Level *c,
                   const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options)
        const override;
    };
}

#endif //LODESTONE_INFDEVZONEIO_H
