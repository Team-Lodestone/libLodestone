//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_MATERIAL_H
#define LODESTONE_MATERIAL_H

#include "Lodestone.Level/types/Color.h"
#include <Lodestone.Common/string/StringSerializable.h>

namespace lodestone::level::material {
    class Material : public common::string::StringSerializable {
      public:
        constexpr Material(const types::Color &color) : mColor(color) {};

        constexpr const types::Color &getColor() const { return mColor; }

        std::string toString() const override {
            return "Material[color=" + mColor.toString() + "]";
        };

      private:
        const types::Color mColor;
    };
} // namespace lodestone::level::material

#endif // LODESTONE_MATERIAL_H
