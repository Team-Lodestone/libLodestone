//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKIO_H
#define LODESTONE_BLOCKIO_H

#include <iostream>
#include <variant>

#include <Lodestone.Common/Defines.h>
#include <Lodestone.Level/Block/State/BlockState.h>

#include "data/AbstractBlockData.h"
// #include "data/BlockData.h"

namespace lodestone::level::conversion::block::version {
    /** Aids with block conversion between versions */
    class LODESTONE_API BlockIO {
    public:
        // TODO: handle converting block states!!!
        // via a separate conversion map
        // TODO: this file is messy!

        virtual ~BlockIO() = default;

        /** Returns a map that maps internal block IDs to a Blk  */
        virtual std::unordered_map<std::string, data::AbstractBlockData*> &getFromInternalConversionMap();
        /** Returns a map that maps Blks to an internal block ID  */
        virtual std::unordered_map<data::AbstractBlockData*, std::string> &getToInternalConversionMap();
        /** Returns a map that maps block IDs to their default data value */
        virtual std::unordered_map<const void *, data::AbstractBlockData*> &getDefaultDataMap();

        void registerBlock(const std::string &internal, data::AbstractBlockData* blk, const bool isDefault = false);

        void registerBlockIfNotExist(const std::string &internal, data::AbstractBlockData* blk, const bool isDefault = false);

        /** Converts an internal block to the BlockIO's format */
        virtual data::AbstractBlockData* convertBlockFromInternal(lodestone::level::block::state::BlockState *b);

        /** Converts a block from BlockIO to the internal format */
        virtual lodestone::level::block::state::BlockState convertBlockToInternal(data::AbstractBlockData *b);

        // /** Reads data into a new Block */
        // virtual lodestone::level::block::state::BlockState readBlock(uint8_t *data) = 0;
        // /** Writes a block to data */
        // virtual void writeBlock(lodestone::level::block::state::BlockState *b, uint8_t *arr) = 0;
    private:
        std::unordered_map<std::string, data::AbstractBlockData*> mFromInternalConversionMap;
        std::unordered_map<data::AbstractBlockData*, std::string> mToInternalConversionMap;
        std::unordered_map<const void *, data::AbstractBlockData*> mDefaultDataMap;
    };
}

#endif //LODESTONE_BLOCKIO_H
