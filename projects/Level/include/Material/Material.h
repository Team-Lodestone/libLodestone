//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_MATERIAL_H
#define LODESTONE_MATERIAL_H
#include "Types/Color.h"

namespace lodestone::level::material {
    class Material {
    public:
        constexpr Material(const Color color) : mColor(color) {};

    private:
        const Color mColor;
    };
}

#endif //LODESTONE_MATERIAL_H
