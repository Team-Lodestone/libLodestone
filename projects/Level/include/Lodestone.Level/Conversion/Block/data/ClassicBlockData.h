//
// Created by DexrnZacAttack on 10/18/25 using zPc-i2.
//
#ifndef LODESTONE_CLASSICBLOCKDATA_H
#define LODESTONE_CLASSICBLOCKDATA_H
#include <variant>

#include "AbstractBlockData.h"
#include "Lodestone.Level/Registry/NamespacedString.h"

namespace lodestone::level::conversion::block::data {
    class ClassicBlockData : public AbstractBlockData {
    public:
        constexpr ClassicBlockData(const uint8_t id) : mId(id) {}

        const void *getId() const override;
        const void *getData() const override;

        const std::type_info &getIdType() const override;
        const std::type_info &getDataType() const override;

        const registry::NamespacedString getTypeName() override;
        const std::type_info &getType() override;

    private:
        const uint8_t mId;
        const std::monostate mData = {};
    };
}

#endif //LODESTONE_BLOCKDATA_H