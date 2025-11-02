//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Level/Conversion/Block/data/NumericBlockData.h"

namespace lodestone::level::conversion::block::data {
    const void * NumericBlockData::getId() const {
        return static_cast<const void *>(&mId);
    }

    const void * NumericBlockData::getData() const {
        return static_cast<const void *>(&mData);
    }

    const std::type_info &NumericBlockData::getIdType() const {
        return typeid(uint8_t);
    }

    const std::type_info &NumericBlockData::getDataType() const {
        return typeid(uint8_t);
    }

    const registry::NamespacedString NumericBlockData::getTypeName() {
        return {"lodestone", "numeric_block_data"};
    }

    const std::type_info & NumericBlockData::getType() {
        return typeid(NumericBlockData);
    }
}
