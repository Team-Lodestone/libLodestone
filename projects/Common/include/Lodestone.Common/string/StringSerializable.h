//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_STRINGSERIALIZABLE_H
#define LODESTONE_STRINGSERIALIZABLE_H
#include <string>

namespace lodestone::common::string {
    /** Java toString clone */
    class StringSerializable {
      public:
        constexpr StringSerializable() = default;

        constexpr virtual ~StringSerializable() = default;

        virtual constexpr operator std::string() const { return toString(); }

        constexpr virtual std::string toString() const = 0;

        constexpr friend std::ostream &operator<<(std::ostream &os,
                                                  const StringSerializable &s) {
            os << s.toString();
            return os;
        };
    };
} // namespace lodestone::common::string

#endif // LODESTONE_STRINGSERIALIZABLE_H