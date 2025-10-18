//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKSTATE_H
#define LODESTONE_BLOCKSTATE_H
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Lodestone.Level/Block/BlockRegistry.h"

namespace lodestone::level::block {
    class Block;
}

namespace lodestone::level::block::state {
    /** Wraps a block with runtime-modifiable "properties" */
    class BlockState {
    public:
        BlockState(const Block *block) : mBlock(block) {};
        BlockState(const char *id) : mBlock(BlockRegistry::sInstance.getBlock(id)) {};
        BlockState(const std::string &id) : mBlock(BlockRegistry::sInstance.getBlock(id)) {};
        BlockState() : mBlock(BlockRegistry::sDefaultBlock) {}
        ~BlockState();

        const std::unordered_map<std::string, std::string> &getStates();

        bool hasProperty(const std::string &id) const;

        const std::string &getProperty(const std::string &id) const;
        std::string &getProperty(const std::string &id);

        const Block *getBlock() const { return mBlock; }

        void setProperty(const std::string &id, const std::string &state);

        const std::string &operator[](const std::string &id) const;
        std::string &operator[](const std::string &id);

    private:
        const Block *mBlock;
        // TODO: it's almost definitely a good idea to figure out how to initialize this only when needed.
        // TODO: also we should be able to store more than strings
        std::unordered_map<std::string, std::string> mProperties;
    };
}

#endif //LODESTONE_BLOCKSTATE_H
