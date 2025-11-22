//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_FLATTENEDBLOCKDATA_H
#define LODESTONE_FLATTENEDBLOCKDATA_H
#include <variant>

#include "Lodestone.Conversion/block/data/AbstractBlockData.h"
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::conversion::block::data {
    class FlattenedBlockData final : public AbstractBlockData {
      public:
        explicit constexpr FlattenedBlockData(const std::string &id)
            : mId(id) {}

        constexpr const std::string &getId() const { return this->mId; };

        const void *getIdPtr() const override;

        const void *getDataPtr() const override;

        const std::type_info &getIdType() const override;

        const std::type_info &getDataType() const override;

        const lodestone::common::registry::Identifier *
        getTypeName() const override;

        const std::type_info &getType() const override;

        constexpr size_t hash() const override {
            return std::hash<std::string>()(mId) ^
                   (std::hash<const lodestone::common::registry::Identifier
                                  *>()(getTypeName())
                    << 8);
        }

        bool equals(const AbstractBlockData *rhs) const override;

        constexpr std::string toString() const override {
            return std::format("FlattenedBlockData[id={}]", mId);
        };

      private:
        const std::string mId;
        const std::monostate mData = {};
    };
} // namespace lodestone::conversion::block::data

#endif // LODESTONE_FLATTENEDBLOCKDATA_H