//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#include <iosfwd>
#include <sstream>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>

// we have Apache ToStringBuilder at home.
class OperatorStringBuilder {
public:
    OperatorStringBuilder(const std::type_info &type) : mType(type) {
        mStream << demangle(type.name()) << "[";
    }

    template<typename T>
    OperatorStringBuilder *addField(const std::string name, const T& v) {
        mStream << name << "=" << v << ",";
        return this;
    }

    #define ADD_FIELD(name) addField(#name, name)

    // TODO: breaks on windows
    static std::string demangle(const char* name) {
        int e = 0;
        char* d = abi::__cxa_demangle(name, nullptr, nullptr, &e);

        std::string r = (!e) ? d : name;
        std::free(d);
        return r;
    }

    operator std::string() {
        return toString();
    }

    std::string toString() {
        std::string s = mStream.str();
        if (!s.empty() && s.back() == ',')
            s.pop_back();

        mStream.str("");
        mStream << s << "]";

        return mStream.str();
    }
private:
    const std::type_info& mType;

    std::stringstream mStream;
};
