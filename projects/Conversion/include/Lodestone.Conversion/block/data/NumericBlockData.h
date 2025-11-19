//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_NUMERICBLOCKDATA_H
#define LODESTONE_NUMERICBLOCKDATA_H
#include <cstdint>

#include "Lodestone.Conversion/block/data/AbstractBlockData.h"
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::conversion::block::data {
    // TODO maybe make this return signed byte
    class NumericBlockData final : public AbstractBlockData {
    public:
        constexpr NumericBlockData(const uint8_t id, const uint8_t data) : mId(id), mData(data) {
        }

        constexpr uint8_t getId() const {
            return this->mId;
        };

        constexpr uint8_t getData() const {
            return this->mData;
        };

        const void *getIdPtr() const override;

        const void *getDataPtr() const override;

        const std::type_info &getIdType() const override;

        const std::type_info &getDataType() const override;

        const lodestone::common::registry::Identifier *getTypeName() const override;

        const std::type_info &getType() const override;

        size_t hash() const override;

        bool equals(const AbstractBlockData *rhs) const override;

        constexpr std::string toString() const override {
            return std::format("NumericBlockData[id={},data={}]", mId, mData);
        };

    private:
        const uint8_t mId;
        const uint8_t mData;
    };
}

#endif //LODESTONE_NUMERICBLOCKDATA_H