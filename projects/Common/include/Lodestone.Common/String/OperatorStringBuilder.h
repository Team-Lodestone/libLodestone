//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#include <iosfwd>
#include <sstream>
#include <typeinfo>

// we have Apache ToStringBuilder at home.
class OperatorStringBuilder {
public:
    OperatorStringBuilder(const std::type_info &type);

    template<typename T>
    OperatorStringBuilder *addField(const std::string name, const T& v) {
        mStream << name << "=" << v << ",";
        return this;
    }

    std::string toString();

    #define ADD_FIELD(name) addField(#name, name)

    // TODO: breaks on windows
    static constexpr const char *demangle(const char* name);

    operator std::string() {
        return toString();
    }

private:
    const std::type_info& mType;
    std::ostringstream mStream;
};
