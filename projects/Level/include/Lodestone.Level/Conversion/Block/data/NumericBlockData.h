//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_NUMERICBLOCKDATA_H
#define LODESTONE_NUMERICBLOCKDATA_H
#include <cstdint>

#include "AbstractBlockData.h"
#include "Lodestone.Level/Registry/NamespacedString.h"

namespace lodestone::level::conversion::block::data {
    class NumericBlockData : public AbstractBlockData {
    public:
        constexpr NumericBlockData(const uint8_t id, const uint8_t data) : mId(id), mData(data) {}

        const void *getId() const override;

        const void *getData() const override;

        const std::type_info &getIdType() const override;

        const std::type_info &getDataType() const override;

        const registry::NamespacedString getTypeName() override;
        const std::type_info &getType() override;
    private:
        const uint8_t mId;
        const uint8_t mData;
    };
}

#endif //LODESTONE_NUMERICBLOCKDATA_H