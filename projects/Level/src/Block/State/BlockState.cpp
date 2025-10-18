//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Block/State/BlockState.h"

namespace lodestone::level::block::state {
    BlockState::~BlockState() {

    }

    const std::unordered_map<std::string, std::string> & BlockState::getStates() {
        return mProperties;
    }

    bool BlockState::hasProperty(const std::string &id) const {
        return mProperties.count(id);
    }

    const std::string & BlockState::getProperty(const std::string &id) const {
        if (const auto it = mProperties.find(id); it != mProperties.end())
            return it->second;

        throw std::runtime_error("Property does not exist");
    }

    std::string & BlockState::getProperty(const std::string &id) {
        return mProperties[id];
    }

    void BlockState::setProperty(const std::string &id, const std::string &state) {
        mProperties[id] = state;
    }

    const std::string & BlockState::operator[](const std::string &id) const {
        return getProperty(id);
    }

    std::string & BlockState::operator[](const std::string &id) {
        return getProperty(id);
    }
}
