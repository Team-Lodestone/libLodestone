//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_NUMERICBLOCKDATA_H
#define LODESTONE_NUMERICBLOCKDATA_H
#include <cstdint>

#include "Lodestone.Conversion/block/data/AbstractBlockData.h"
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::conversion::block::data {
    class NumericBlockData final : public AbstractBlockData {
      public:
        constexpr NumericBlockData(const uint8_t id, const uint8_t data)
            : m_id(id), m_data(data) {}

        constexpr uint8_t getId() const { return this->m_id; };

        constexpr uint8_t getData() const { return this->m_data; };

        const void *getIdPtr() const override;

        const void *getDataPtr() const override;

        const std::type_info &getIdType() const override;

        const std::type_info &getDataType() const override;

        const lodestone::common::registry::Identifier *
        getTypeName() const override;

        const std::type_info &getType() const override;

        size_t hash() const override;

        bool equals(const AbstractBlockData *rhs) const override;

        constexpr std::string toString() const override {
            return std::format("NumericBlockData[id={},data={}]", m_id, m_data);
        };

      private:
        const uint8_t m_id;
        const uint8_t m_data;
    };
} // namespace lodestone::conversion::block::data

#endif // LODESTONE_NUMERICBLOCKDATA_H