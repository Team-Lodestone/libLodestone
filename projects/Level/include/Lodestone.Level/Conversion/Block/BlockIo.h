//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKIO_H
#define LODESTONE_BLOCKIO_H

#include <iostream>
#include <variant>

#include <Lodestone.Common/Defines.h>
#include <Lodestone.Level/Block/State/BlockState.h>

struct PairHash {
    template <class F, class S>
    std::size_t operator()(const std::pair<F, S>& p) const {
        return std::hash<F>{}(p.first) ^ (std::hash<S>{}(p.second) << 1);
    }
};

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
        virtual std::unordered_map<std::string, Blk> &getFromInternalConversionMap() = 0;
        /** Returns a map that maps Blks to an internal block ID  */
        virtual std::unordered_map<Blk, std::string, PairHash> &getToInternalConversionMap() = 0;
        /** Returns a map that maps block IDs to their default data value */
        virtual std::unordered_map<B, D> &getDefaultDataMap() = 0;

        void registerBlock(const std::string &internal, Blk blk, const bool isDefault = false) {
            std::unordered_map<std::string, Blk> &c = getFromInternalConversionMap();
            std::unordered_map<Blk, std::string, PairHash> &i = getToInternalConversionMap();

            c[internal] = blk;
            i[blk] = internal;
            if (isDefault) {
                std::unordered_map<B, D> &d = getDefaultDataMap();
                d[blk.first] = blk.second;
            }
        }

        /** Converts an internal block to the BlockIO's format */
        virtual Blk convertBlockFromInternal(lodestone::level::block::state::BlockState *b) {
            const std::unordered_map<std::string, Blk> &m = getFromInternalConversionMap();
            const std::string id = b->getBlock()->getID();

            if (m.count(id)) return m.at(id);

            return Blk();
        };

        /** Converts a block from BlockIO to the internal format */
        virtual lodestone::level::block::state::BlockState convertBlockToInternal(B id, D data) {
            const std::unordered_map<Blk, std::string, PairHash> &m = getToInternalConversionMap();

            if (auto it = m.find({id, data}); it != m.end()) {
                // if we have block ID with state in conversion map, return it
                return lodestone::level::block::state::BlockState(it->second);
            }

            // otherwise, if we have block id with default value, return that
            const auto& d = getDefaultDataMap();
            if (auto it = d.find(id); it != d.end()) {
                if (auto itr = m.find({id, it->second}); itr != m.end()) {
                    return lodestone::level::block::state::BlockState(itr->second);
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
