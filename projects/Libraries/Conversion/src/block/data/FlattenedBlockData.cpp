//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/data/FlattenedBlockData.h"

namespace lodestone::conversion::block::data {
    constexpr const void *FlattenedBlockData::getIdPtr() const { return &m_id; }

    constexpr const void *FlattenedBlockData::getDataPtr() const { return &m_data; }

    constexpr const std::type_info &FlattenedBlockData::getIdType() const {
        return typeid(const std::string);
    }

    constexpr const std::type_info &FlattenedBlockData::getDataType() const {
        return typeid(std::monostate);
    }

    constexpr const lodestone::common::registry::Identifier *
    FlattenedBlockData::getTypeName() const {
        return &identifiers::FLATTENED_BLOCK_DATA;
    }

    constexpr const std::type_info &FlattenedBlockData::getType() const {
        return typeid(FlattenedBlockData);
    }

    constexpr bool FlattenedBlockData::equals(
        const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const FlattenedBlockData *>(rhs))
            return c->m_id == m_id && c->getTypeName() == getTypeName();

        return false;
    }
} // namespace lodestone::conversion::block::data