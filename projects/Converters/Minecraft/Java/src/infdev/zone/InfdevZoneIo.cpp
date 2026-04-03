/** @file InfdevZoneIo.cpp
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevZoneIo.h"

#include "BinaryIO/container/FixedArray.h"
#include "BinaryIO/stream/BinaryInputStream.h"
#include "Lodestone.Conversion/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevChunkIo.h"
#include "Lodestone.Minecraft.Java/infdev/InfdevZone.h"

#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include "Lodestone.Minecraft.Java/infdev/InfdevChunk.h"

namespace lodestone::minecraft::java::infdev::zone {
    std::unique_ptr<level::Level> InfdevZoneIo::read(
        const common::conversion::io::options::OptionPresets::CommonChunkReadOptions &options) const {
        auto bis = bio::stream::BinaryInputStream(options.input);

        auto zone = std::make_unique<InfdevZone>(options.coords);
        const chunk::InfdevChunkIO *chunkIo = this->getAsByRelation<const chunk::InfdevChunkIO, &
            conversion::identifiers::CHUNK_IO>();


        if (const uint32_t magic = bis.readBE<uint32_t>(); magic != 0x13737000) {
            throw std::runtime_error{std::format("Invalid magic value! Expected: {}, read: {}", EXPECTED_MAGIC, magic)};
        }

        if (const uint16_t version = bis.readBE<uint16_t>(); version != 0) {
            throw std::runtime_error{std::format("Unexpected world version! Expected: {}, read: {}", 0, version)};
        }

        // Read slot indices
        const uint16_t slotCount = bis.readBE<uint16_t>();
        auto slots = bio::container::FixedArray<uint16_t>(slotCount);
        for (int i = 0; i < slotCount; i++) {
            slots[i] = bis.readBE<uint16_t>();
        }

        for (const uint16_t slot : slots) {
            if (slot == 0) continue;

            // TODO: Make this less jank / not reliant on seek
            const uint64_t readPos = static_cast<uint64_t>(slot) * (32768 * 3 + 256) + 4096;
            bis.seek(readPos);

            auto c = CAST_UNIQUE_PTR(chunk::InfdevChunk,
                                     chunkIo->read(common::conversion::io::options::OptionPresets::CommonReadOptions {
                                         conversion::io::options::fs::file::FileReaderOptions {
                                         options.input,
                                         },
                                         conversion::io::options::versioned::VersionedOptions {
                                         options.version
                                         }
                                         }));
            if (c != nullptr) {
                zone->addChunk(std::move(c));
            } else {
                throw std::runtime_error{"Failed to read chunk from InfdevZoneIo"};
            }
        }

        return zone;
    }

    void InfdevZoneIo::write(level::Level *c,
                             const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options)
    const {
    }
}
