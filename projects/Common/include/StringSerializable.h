//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_STRINGSERIALIZABLE_H
#define LODESTONE_STRINGSERIALIZABLE_H
#include <string>

#include "OperatorStringBuilder.h"

class StringSerializable {
public:
    virtual ~StringSerializable() = default;

    operator std::string() const {
        return toString();
    }

    virtual std::string toString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const StringSerializable& s) {
        os << s.toString();
        return os;
    };
};

#endif //LODESTONE_STRINGSERIALIZABLE_H