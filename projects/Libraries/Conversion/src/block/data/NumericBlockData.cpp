//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/data/NumericBlockData.h"

namespace lodestone::conversion::block::data {
    const void *NumericBlockData::getIdPtr() const {
        return static_cast<const void *>(&m_id);
    }

    const void *NumericBlockData::getDataPtr() const {
        return static_cast<const void *>(&m_data);
    }

    const std::type_info &NumericBlockData::getIdType() const {
        return typeid(uint8_t);
    }

    const std::type_info &NumericBlockData::getDataType() const {
        return typeid(uint8_t);
    }

    const lodestone::common::registry::Identifier *
    NumericBlockData::getTypeName() const {
        return &identifiers::NUMERIC_BLOCK_DATA;
    }

    const std::type_info &NumericBlockData::getType() const {
        return typeid(NumericBlockData);
    }

    size_t NumericBlockData::hash() const {
        return std::hash<uint8_t>()(m_id) ^ std::hash<uint8_t>()(m_data) << 8 ^
               (std::hash<const lodestone::common::registry::Identifier *>()(
                    getTypeName())
                << 16);
    }

    bool NumericBlockData::equals(const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const NumericBlockData *>(rhs))
            return c->m_id == m_id && c->m_data == m_data &&
                   c->getTypeName() == getTypeName();

        return false;
    }
} // namespace lodestone::conversion::block::data