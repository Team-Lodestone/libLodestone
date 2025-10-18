//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_MATERIAL_H
#define LODESTONE_MATERIAL_H

#include "Lodestone.Level/Types/Color.h"

namespace lodestone::level::material {
    class Material final {
    public:
        constexpr Material(const types::Color color) : mColor(color) {};

        constexpr const types::Color &getColor() const { return mColor; }
    private:
        const types::Color mColor;
    };
}

#endif //LODESTONE_MATERIAL_H
