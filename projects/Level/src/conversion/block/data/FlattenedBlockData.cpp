//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Level/conversion/block/data/FlattenedBlockData.h"

namespace lodestone::level::conversion::block::data {
    const void * FlattenedBlockData::getIdPtr() const {
        return &mId;
    }

    const void * FlattenedBlockData::getDataPtr() const {
        return &mData;
    }

    const std::type_info & FlattenedBlockData::getIdType() const {
        return typeid(const std::string);
    }

    const std::type_info & FlattenedBlockData::getDataType() const {
        return typeid(std::monostate);
    }

    const lodestone::level::registry::NamespacedString *FlattenedBlockData::getTypeName() const {
        return &identifiers::FLATTENED_BLOCK_DATA;
    }

    const std::type_info & FlattenedBlockData::getType() const {
        return typeid(FlattenedBlockData);
    }

    bool FlattenedBlockData::equals(const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const FlattenedBlockData*>(rhs))
            return c->mId == mId && c->getTypeName() == getTypeName();

        return false;
    }
}