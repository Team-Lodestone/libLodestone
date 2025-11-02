//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Level/Conversion/Block/data/ClassicBlockData.h"

namespace lodestone::level::conversion::block::data {
    const void * ClassicBlockData::getId() const {
        return static_cast<const void *>(&mId);
    }

    const void * ClassicBlockData::getData() const {
        return static_cast<const void *>(&mData);
    }

    const std::type_info & ClassicBlockData::getIdType() const {
        return typeid(uint8_t);
    }

    const std::type_info & ClassicBlockData::getDataType() const {
        return typeid(std::monostate);
    }

    const lodestone::level::registry::NamespacedString ClassicBlockData::getTypeName() {
        return {"lodestone", "classic_block_data"};
    }

    const std::type_info & ClassicBlockData::getType() {
        return typeid(ClassicBlockData);
    }
}
