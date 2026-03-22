//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_MATERIAL_H
#define LODESTONE_MATERIAL_H

#include "Lodestone.Level/types/Color.h"
#include <Lodestone.Common/string/StringSerializable.h>

namespace lodestone::level::material {
    class LODESTONE_LEVEL_API Material : public common::string::StringSerializable {
      public:
        constexpr Material(const types::Color &color) : m_color(color) {};

        constexpr const types::Color &getColor() const { return m_color; }

        std::string toString() const override {
            return "Material[color=" + m_color.toString() + "]";
        };

      private:
        const types::Color m_color;
    };
} // namespace lodestone::level::material

#endif // LODESTONE_MATERIAL_H
