//
// Created by DexrnZacAttack on 11/23/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/data/ExtendedNumericBlockData.h"

namespace lodestone::conversion::block::data {
    const void *ExtendedNumericBlockData::getIdPtr() const {
        return &mId;
    }

    const void *ExtendedNumericBlockData::getDataPtr() const {
        return &mData;
    }

    const std::type_info &ExtendedNumericBlockData::getIdType() const {
        return typeid(uint8_t);
    }

    const std::type_info &ExtendedNumericBlockData::getDataType() const {
        return typeid(uint8_t);
    }

    const lodestone::common::registry::Identifier *
    ExtendedNumericBlockData::getTypeName() const {
        return &identifiers::EXTENDED_NUMERIC_BLOCK_DATA;
    }

    const std::type_info &ExtendedNumericBlockData::getType() const {
        return typeid(ExtendedNumericBlockData);
    }

    size_t ExtendedNumericBlockData::hash() const {
        return std::hash<uint16_t>()(mId) ^ std::hash<uint8_t>()(mData) << 8 ^
               (std::hash<const lodestone::common::registry::Identifier *>()(
                    getTypeName())
                << 16);
    }

    bool ExtendedNumericBlockData::equals(const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const ExtendedNumericBlockData *>(rhs))
            return c->mId == mId && c->mData == mData &&
                   c->getTypeName() == getTypeName();

        return false;
    }
}
