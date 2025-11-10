//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

#include <iosfwd>
#include <sstream>
#include <typeinfo>

// we have Apache ToStringBuilder at home.
class OperatorStringBuilder {
public:
    OperatorStringBuilder(const std::type_info &type) : mType(type) {
        mStream << demangle(type.name()) << "[";
    };

    template<typename T>
    constexpr OperatorStringBuilder *addField(const std::string &name, const T &v) {
        mStream << name << "=" << v << ",";
        return this;
    }

    constexpr std::string toString() {
        std::string s = mStream.str();
        if (!s.empty() && s.back() == ',')
            s.pop_back();

        mStream.str("");
        mStream << s << "]";

        return mStream.str();
    };

#define ADD_FIELD(name) addField(#name, name)

    // TODO: breaks on windows
    static constexpr const char *demangle(const char *name) {
#if defined(__GNUC__) || defined(__clang__)
        int err = 0;
        char *demangled = abi::__cxa_demangle(name, nullptr, nullptr, &err);

        const char *r = (!err) ? demangled : name;
        std::free(demangled);
        return r;
#else
        return name;
#endif
    }

    constexpr operator std::string() {
        return toString();
    }

private:
    const std::type_info &mType;
    std::ostringstream mStream;
};