//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/data/ClassicBlockData.h"

namespace lodestone::conversion::block::data {
    const void *ClassicBlockData::getIdPtr() const {
        return &mId;
    }

    const void *ClassicBlockData::getDataPtr() const {
        return &mData;
    }

    const std::type_info &ClassicBlockData::getIdType() const {
        return typeid(uint8_t);
    }

    const std::type_info &ClassicBlockData::getDataType() const {
        return typeid(std::monostate);
    }

    const lodestone::common::registry::NamespacedString *ClassicBlockData::getTypeName() const {
        return &identifiers::CLASSIC_BLOCK_DATA;
    }

    const std::type_info &ClassicBlockData::getType() const {
        return typeid(ClassicBlockData);
    }

    bool ClassicBlockData::equals(const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const ClassicBlockData *>(rhs))
            return c->mId == mId && c->getTypeName() == getTypeName();

        return false;
    }
}