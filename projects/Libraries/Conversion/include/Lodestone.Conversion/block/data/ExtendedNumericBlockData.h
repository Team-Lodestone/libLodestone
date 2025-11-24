//
// Created by DexrnZacAttack on 11/23/25 using zPc-i2.
//
#ifndef LODESTONE_EXTENDEDNUMERICBLOCKDATA_H
#define LODESTONE_EXTENDEDNUMERICBLOCKDATA_H
#include "Lodestone.Conversion/block/data/AbstractBlockData.h"

namespace lodestone::conversion::block::data {
    // Early anvil added block id support for ids ranging from 0-4096, this was determined by an extra 4 bits stored in parallel with each section's block array
    class ExtendedNumericBlockData : public AbstractBlockData {
    public:
        constexpr ExtendedNumericBlockData(const uint16_t id, const uint8_t data)
            : mId(id), mData(data) {}

        constexpr uint16_t getId() const { return this->mId; };

        constexpr uint8_t getData() const { return this->mData; };

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
            return std::format("ExtendedNumericBlockData[id={},data={}]", mId, mData);
        };

    private:
        const uint16_t mId;
        const uint8_t mData;
    };
}

#endif // LODESTONE_EXTENDEDNUMERICBLOCKDATA_H
