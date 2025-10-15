//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKS_H
#define LODESTONE_BLOCKS_H
#include "Block.h"
#include "Defines.h"

namespace lodestone::level::block {
    class LODESTONE_API Blocks {
    protected:
        Blocks();
    public:
        static Blocks *sInstance;

        void registerBlock(const std::string &id, const Block* block) {
            if (mBlocks.count(id))
                throw std::runtime_error("Block already exists");

            mBlocks[id] = std::move(block);
        }

        const Block *getBlock(const std::string &id) const {
            if (!mBlocks.count(id))
                return nullptr;

            return mBlocks.at(id);
        };
    private:
        std::unordered_map<std::string, const Block*> mBlocks = {
            {"lodestone:air", new Block("lodestone:air", material::Material({0, 0, 0, 0}))}
        };
    };
}

#endif //LODESTONE_BLOCKS_H