//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKIO_H
#define LODESTONE_BLOCKIO_H

#include <iostream>
#include <variant>

#include "Defines.h"
#include "Block/State/BlockState.h"

namespace lodestone::level::conversion::block {
    template <typename B, typename D = std::monostate> class LODESTONE_API BlockIO {
    protected:
        BlockIO() {}
    public:
        // TODO: handle converting block states!!!
        // via a separate conversion map
        // TODO: this file is messy!
        /**
         * B: Block ID type
         *
         * D: Block data type (e.g variant)
         */
        using Blk = std::pair<B, D>;

        virtual ~BlockIO() = default;

        /** Returns a map that maps internal block IDs to a Blk  */
        virtual std::unordered_map<std::string, Blk> &getConversionMap() = 0;
        /** Returns a map that maps block IDs to their default data value */
        virtual std::unordered_map<B, D> &getDefaultDataMap() = 0;

        void registerBlock(const std::string &internal, Blk blk, const bool isDefault = false) {
            std::unordered_map<std::string, Blk> &c = getConversionMap();

            c[internal] = blk;
            if (isDefault) {
                std::unordered_map<B, D> &d = getDefaultDataMap();
                d[blk.first] = blk.second;
            }

            std::cout << "Registered block " << internal << " as " << blk.first << std::endl;
        }

        /** Converts an internal block to the BlockIO's format */
        virtual Blk convertBlockFromInternal(lodestone::level::block::state::BlockState *b) {
            const std::unordered_map<std::string, std::pair<B, D>> &m = getConversionMap();
            const std::string id = b->getBlock()->getID();

            if (m.count(id)) return m.at(id);

            return Blk();
        };

        /** Converts a block from BlockIO to the internal format */
        virtual lodestone::level::block::state::BlockState convertBlockToInternal(B id, D data) {
            const std::unordered_map<std::string, std::pair<B, D>> &m = getConversionMap();

            for (const auto& [bid, blk] : m) {
                // if we have block ID with state in conversion map, return it
                if (blk.first == id && blk.second == data)
                    return lodestone::level::block::state::BlockState(bid);
            }

            // otherwise, if we have block id with default value, return that
            std::unordered_map<B, D> &d = getDefaultDataMap();
            if (d.count(id)) {
                D dd = d.at(id);
                for (const auto& [i, blk] : m) {
                    if (blk.first == id && blk.second == dd)
                        return lodestone::level::block::state::BlockState(i);
                }
            }

            throw std::runtime_error("Could not find block with ID: " + id);
        };

        /** Reads data into a new Block */
        virtual lodestone::level::block::state::BlockState readBlock(uint8_t *data) = 0;
        /** Writes a block to data */
        virtual void writeBlock(lodestone::level::block::state::BlockState *b, uint8_t *arr) = 0;
    protected:
        D mDef;
    };
}

#endif //LODESTONE_BLOCKIO_H
