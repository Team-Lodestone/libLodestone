//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_CLASSICBLOCKDATA_H
#define LODESTONE_CLASSICBLOCKDATA_H
#include <variant>

#include "Lodestone.Conversion/block/data/AbstractBlockData.h"

#include <Lodestone.Common/registry/Identifier.h>
#include <cstdint>

namespace lodestone::conversion::block::data {
    class ClassicBlockData final : public AbstractBlockData {
      public:
        explicit constexpr ClassicBlockData(const uint8_t id) : mId(id) {}

        constexpr uint8_t getId() const { return this->mId; };

        const void *getIdPtr() const override;

        const void *getDataPtr() const override;

        const std::type_info &getIdType() const override;

        const std::type_info &getDataType() const override;

        const lodestone::common::registry::Identifier *
        getTypeName() const override;

        const std::type_info &getType() const override;

        constexpr size_t hash() const override {
            return std::hash<uint8_t>()(mId) ^
                   (std::hash<const lodestone::common::registry::Identifier
                                  *>()(getTypeName())
                    << 8);
        }

        bool equals(const AbstractBlockData *rhs) const override;

        constexpr std::string toString() const override {
            return std::format("ClassicBlockData[id={}]", mId);
        };

      private:
        const uint8_t mId;
        const std::monostate mData = {};
    };
} // namespace lodestone::conversion::block::data

#endif // LODESTONE_BLOCKDATA_H