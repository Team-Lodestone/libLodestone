//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTBLOCKDATA_H
#define LODESTONE_ABSTRACTBLOCKDATA_H

#include "Lodestone.Level/Registry/NamespacedString.h"

namespace lodestone::level::conversion::block::data {
    class AbstractBlockData {
    public:
        virtual ~AbstractBlockData() = default;

        virtual const void *getId() const = 0;
        virtual const void *getData() const = 0;

        virtual const std::type_info &getIdType() const = 0;
        virtual const std::type_info &getDataType() const = 0;

        virtual const std::type_info &getType() = 0;
        virtual const registry::NamespacedString getTypeName() = 0;
    };
}

#endif //LODESTONE_ABSTRACTBLOCKDATA_H