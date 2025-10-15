//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKSTATE_H
#define LODESTONE_BLOCKSTATE_H
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "../Blocks.h"

namespace lodestone::level::block {
    class Block;
}

namespace lodestone::level::block::state {
    /** Wraps a block with runtime-modifiable "properties" */
    class BlockState {
    public:
        BlockState(const Block *block) : mBlock(block) {};
        BlockState(const char *id) : mBlock(Blocks::sInstance->getBlock(id)) {};
        BlockState() : mBlock(Blocks::sDefaultBlock) {}
        ~BlockState();

        const Block *getBlock() const { return mBlock; }

        const std::unordered_map<std::string, std::string> &getStates() {
            return mProperties;
        }

        bool hasProperty(const std::string &id) const {
            return mProperties.count(id);
        }

        const std::string &getProperty(const std::string &id) const {
            if (!mProperties.count(id))
                throw std::runtime_error("Property does not exist");

            return mProperties.at(id);
        }

        std::string &getProperty(const std::string &id) {
            return mProperties[id];
        }

        void setState(const std::string &id, const std::string &state) {
            mProperties[id] = state;
        }

        const std::string &operator[](const std::string &id) const {
            return getProperty(id);
        }

        std::string &operator[](const std::string &id) {
            return getProperty(id);
        }

    private:
        const Block *mBlock;
        // TODO: it's almost definitely a good idea to figure out how to initialize this only when needed.
        // TODO: also we should be able to store more than strings
        std::unordered_map<std::string, std::string> mProperties;
    };
}

#endif //LODESTONE_BLOCKSTATE_H
