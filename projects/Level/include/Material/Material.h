//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_MATERIAL_H
#define LODESTONE_MATERIAL_H
#include <string>

#include "Types/Color.h"

namespace lodestone::level::material {
    class Material {
    public:
        constexpr Material(const Color color) : mColor(color) {};

        operator std::string() const {
            return toString();
        }

        std::string toString() const {
            return (new OperatorStringBuilder(typeid(*this)))
            ->ADD_FIELD(mColor)
            ->toString();
        }

        friend std::ostream& operator<<(std::ostream& os, const Material& material) {
            os << material.toString();
            return os;
        };
    private:
        const Color mColor;
    };
}

#endif //LODESTONE_MATERIAL_H
