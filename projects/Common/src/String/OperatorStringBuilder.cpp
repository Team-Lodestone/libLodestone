//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "String/OperatorStringBuilder.h"

constexpr const char *OperatorStringBuilder::demangle(const char *name) {
    int err = 0;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &err);

    const char *r = (!err) ? demangled : name;
    std::free(demangled);
    return r;
}

OperatorStringBuilder::OperatorStringBuilder(const std::type_info &type) : mType(type) {
    mStream << demangle(type.name()) << "[";
}

std::string OperatorStringBuilder::toString() {
    std::string s = mStream.str();
    if (!s.empty() && s.back() == ',')
        s.pop_back();

    mStream.str("");
    mStream << s << "]";

    return mStream.str().c_str();
}
