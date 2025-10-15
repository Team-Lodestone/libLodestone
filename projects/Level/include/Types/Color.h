//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once

#include "OperatorStringBuilder.h"

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    operator std::string() const {
        return this->toString();
    }

    std::string toString() const {
        return (new OperatorStringBuilder(typeid(*this)))
        ->addField("r", static_cast<int>(r))
        ->addField("g", static_cast<int>(g))
        ->addField("b", static_cast<int>(b))
        ->addField("a", static_cast<int>(a))
        ->toString();
    }

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << color.toString();
        return os;
    };
};