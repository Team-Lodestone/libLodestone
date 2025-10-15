//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKSTATE_H
#define LODESTONE_BLOCKSTATE_H
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Blocks.h"

namespace lodestone::level::block {
    class Block;

    class BlockState {
    public:
        BlockState(const Block *block) : mBlock(block) {};
        BlockState(const char *id) : mBlock(Blocks::sInstance->getBlock(id)) {};
        BlockState() : mBlock(Blocks::sInstance->getBlock("lodestone:air")) {}
        ~BlockState();

        const Block *getBlock() const { return mBlock; }

        const std::unordered_map<std::string, std::string> &getStates() {
            return mStates;
        }

        bool hasState(const std::string &id) const {
            return mStates.count(id);
        }

        const std::string &getState(const std::string &id) const {
            if (!mStates.count(id))
                throw std::runtime_error("State does not exist");

            return mStates.at(id);
        }

        std::string &getState(const std::string &id) {
            return mStates[id];
        }

        void setState(const std::string &id, const std::string &state) {
            mStates[id] = state;
        }

        const std::string &operator[](const std::string &id) const {
            return getState(id);
        }

        std::string &operator[](const std::string &id) {
            return getState(id);
        }

    private:
        const Block *mBlock;
        // TODO: it's almost definitely a good idea to figure out how to initialize this only when needed.
        std::unordered_map<std::string, std::string> mStates;
    };
}

#endif //LODESTONE_BLOCKSTATE_H
