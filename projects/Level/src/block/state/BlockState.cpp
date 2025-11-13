//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/block/state/BlockState.h"
#include <memory>
#include <gtl/phmap.hpp>

namespace lodestone::level::block::state {
    const gtl::flat_hash_map<std::string, std::string> BlockState::EMPTY_PROPERTIES{};

    const gtl::flat_hash_map<std::string, std::string> &BlockState::getStates() const {
        if (!mProperties) return EMPTY_PROPERTIES;
        return *mProperties;
    }

    bool BlockState::hasProperty(const std::string &id) const {
        if (!mProperties) return false;
        return mProperties->contains(id);
    }

    const std::string &BlockState::getProperty(const std::string &id) const {
        if (mProperties)
            if (const auto it = mProperties->find(id); it != mProperties->end())
                return it->second;

        throw std::runtime_error("Property does not exist");
    }

    std::string &BlockState::getProperty(const std::string &id) {
        if (mProperties)
            if (const auto it = mProperties->find(id); it != mProperties->end())
                return it->second;

        throw std::runtime_error("Property does not exist");
    }

    void BlockState::setProperty(const std::string &id, const std::string &state) {
        if (!mProperties) mProperties = gtl::flat_hash_map<std::string, std::string>();
        mProperties.value()[id] = state;
    }

    const std::string &BlockState::operator[](const std::string &id) const {
        return getProperty(id);
    }

    std::string &BlockState::operator[](const std::string &id) {
        return getProperty(id);
    }
}