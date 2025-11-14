//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/data/NumericBlockData.h"

namespace lodestone::conversion::block::data {
    const void *NumericBlockData::getIdPtr() const {
        return static_cast<const void *>(&mId);
    }

    const void *NumericBlockData::getDataPtr() const {
        return static_cast<const void *>(&mData);
    }

    const std::type_info &NumericBlockData::getIdType() const {
        return typeid(uint8_t);
    }

    const std::type_info &NumericBlockData::getDataType() const {
        return typeid(uint8_t);
    }

    const lodestone::common::registry::NamespacedString *NumericBlockData::getTypeName() const {
        return &identifiers::NUMERIC_BLOCK_DATA;
    }

    const std::type_info &NumericBlockData::getType() const {
        return typeid(NumericBlockData);
    }

    size_t NumericBlockData::hash() const {
        return std::hash<uint8_t>()(mId) ^ std::hash<uint8_t>()(mData) << 8 ^ (
                   std::hash<const lodestone::common::registry::NamespacedString *>()(getTypeName()) << 16);
    }

    bool NumericBlockData::equals(const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const NumericBlockData *>(rhs))
            return c->mId == mId && c->mData == mData && c->getTypeName() == getTypeName();

        return false;
    }
}