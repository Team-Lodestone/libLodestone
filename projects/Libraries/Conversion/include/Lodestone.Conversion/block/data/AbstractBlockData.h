//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTBLOCKDATA_H
#define LODESTONE_ABSTRACTBLOCKDATA_H

#include "Lodestone.Conversion/Identifiers.h"
#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::block::data {
    //todo try to see if we can move subclasses to lodestone::minecraft::common
    class LODESTONE_CONVERSION_API AbstractBlockData
        : public lodestone::common::string::StringSerializable {
      public:
        struct LODESTONE_CONVERSION_API Comparator {
            bool operator()(
                const lodestone::conversion::block::data::AbstractBlockData *lhs,
                const lodestone::conversion::block::data::AbstractBlockData *rhs) const {
                return lhs->equals(rhs);
            }
        };

        constexpr ~AbstractBlockData() override = default;

        std::string toString() const override {
            return *this->getTypeName();
        };

        constexpr virtual size_t hash() const = 0;

        constexpr virtual bool equals(const AbstractBlockData *rhs) const = 0;

        constexpr virtual const void *getIdPtr() const = 0;

        constexpr virtual const void *getDataPtr() const = 0;

        constexpr virtual const std::type_info &getIdType() const = 0;

        constexpr virtual const std::type_info &getDataType() const = 0;

        constexpr virtual const std::type_info &getType() const = 0;

        constexpr virtual const lodestone::common::registry::Identifier *
        getTypeName() const {
            return &lodestone::conversion::identifiers::ABSTRACT_BLOCK_DATA;
        };

        template <class T> constexpr const T *as() const {
            return dynamic_cast<const T *>(this);
        }

        constexpr bool operator==(const AbstractBlockData &rhs) const {
            return this->equals(&rhs);
        }
    };

} // namespace lodestone::conversion::block::data

namespace std {
    template <>
    struct LODESTONE_CONVERSION_API hash<lodestone::conversion::block::data::AbstractBlockData *> {
        size_t operator()(
            const lodestone::conversion::block::data::AbstractBlockData *blk) const noexcept {
            return blk->hash();
        }
    };
}


#endif // LODESTONE_ABSTRACTBLOCKDATA_H