//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTBLOCKDATA_H
#define LODESTONE_ABSTRACTBLOCKDATA_H

#include "Lodestone.Level/registry/NamespacedString.h"
#include "Lodestone.Common/String/StringSerializable.h"
#include "Lodestone.Level/Identifiers.h"

namespace lodestone::level::conversion::block::data {
    class AbstractBlockData : public StringSerializable {
    public:
        constexpr ~AbstractBlockData() override = default;

        constexpr std::string toString() const override {
            return *this->getTypeName();
        };

        constexpr virtual size_t hash() const = 0;
        constexpr virtual bool equals(const AbstractBlockData* rhs) const = 0;

        constexpr virtual const void *getIdPtr() const = 0;
        constexpr virtual const void *getDataPtr() const = 0;

        constexpr virtual const std::type_info &getIdType() const = 0;
        constexpr virtual const std::type_info &getDataType() const = 0;

        constexpr virtual const std::type_info &getType() const = 0;
        constexpr virtual const registry::NamespacedString *getTypeName() const {
            return &identifiers::ABSTRACT_BLOCK_DATA;
        };

        template<class T>
        constexpr const T *as() const {
            return dynamic_cast<const T*>(this);
        }

        constexpr bool operator==(const AbstractBlockData& rhs) const {
            return this->equals(&rhs);
        }
    };
}

#endif //LODESTONE_ABSTRACTBLOCKDATA_H