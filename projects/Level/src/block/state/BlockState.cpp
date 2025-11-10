//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/block/state/BlockState.h"

namespace lodestone::level::block::state {
    BlockState::~BlockState() {
    }

    const gtl::flat_hash_map<std::string, std::string> &BlockState::getStates() {
        return mProperties;
    }

    bool BlockState::hasProperty(const std::string &id) const {
        return mProperties.contains(id);
    }

    const std::string &BlockState::getProperty(const std::string &id) const {
        if (const auto it = mProperties.find(id); it != mProperties.end())
            return it->second;

        throw std::runtime_error("Property does not exist");
    }

    std::string &BlockState::getProperty(const std::string &id) {
        return mProperties[id];
    }

    void BlockState::setProperty(const std::string &id, const std::string &state) {
        mProperties[id] = state;
    }

    const std::string &BlockState::operator[](const std::string &id) const {
        return getProperty(id);
    }

    std::string &BlockState::operator[](const std::string &id) {
        return getProperty(id);
    }
}