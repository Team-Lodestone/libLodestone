//
// Created by DexrnZacAttack on 11/23/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/data/ExtendedNumericBlockData.h"

namespace lodestone::conversion::block::data {
    const void *ExtendedNumericBlockData::getIdPtr() const { return &m_id; }

    const void *ExtendedNumericBlockData::getDataPtr() const { return &m_data; }

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
        return std::hash<uint16_t>()(m_id) ^ std::hash<uint8_t>()(m_data) << 8 ^
               (std::hash<const lodestone::common::registry::Identifier *>()(
                    getTypeName())
                << 16);
    }

    bool ExtendedNumericBlockData::equals(const AbstractBlockData *rhs) const {
        if (const auto c = dynamic_cast<const ExtendedNumericBlockData *>(rhs))
            return c->m_id == m_id && c->m_data == m_data &&
                   c->getTypeName() == getTypeName();

        return false;
    }
} // namespace lodestone::conversion::block::data
