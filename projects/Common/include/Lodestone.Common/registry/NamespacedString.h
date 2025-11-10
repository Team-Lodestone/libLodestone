//
// Created by DexrnZacAttack on 10/17/25 using zPc-i2.
//
#ifndef LODESTONE_NAMESPACEDSTRING_H
#define LODESTONE_NAMESPACEDSTRING_H
#include <format>
#include <cstring>
#include "Lodestone.Common/string/StringSerializable.h"

// this class required me to upgrade to c++20
namespace lodestone::common::registry {
    class NamespacedString : public StringSerializable {
    protected:
        explicit constexpr NamespacedString(const char *name) noexcept : mNamespace("lodestone"), mName(name) {
        };

    public:
        constexpr NamespacedString(const char *nmsp, const char *name) noexcept : mNamespace(nmsp), mName(name) {
        };

        constexpr const char *getName() const noexcept {
            return mName;
        }

        constexpr const char *getNamespace() const noexcept {
            return mNamespace;
        }

        constexpr std::string getString() const noexcept {
            return std::string(mNamespace) + ":" + mName;
        }

        constexpr std::string toString() const override {
            return getString();
        };

        constexpr bool operator==(const NamespacedString &rhs) const noexcept {
            return this->mName == rhs.mName && this->mNamespace == rhs.mNamespace;
        }

        constexpr operator std::string() const noexcept {
            return getString();
        }

        constexpr friend std::ostream &operator<<(std::ostream &os, const NamespacedString &s) noexcept {
            os << s.getString();
            return os;
        }

    private:
        const char *mNamespace;
        const char *mName;
    };
}

template<>
struct std::formatter<lodestone::common::registry::NamespacedString> : formatter<string> {
    std::format_context::iterator format(const lodestone::common::registry::NamespacedString &s,
                                         format_context &c) const {
        return formatter<string>::format(s.getString(), c);
    }
};

struct NamespacedStringHasher {
    size_t operator()(const lodestone::common::registry::NamespacedString &s) const noexcept {
        return std::hash<std::string_view>{}(s.getName())
               ^ (std::hash<std::string_view>{}(s.getNamespace()) << 1);
    }
};

struct NamespacedStringComparator {
    bool operator()(const lodestone::common::registry::NamespacedString &lhs,
                    const lodestone::common::registry::NamespacedString &rhs) const noexcept {
        return !std::strcmp(lhs.getNamespace(), rhs.getNamespace()) &&
               !std::strcmp(lhs.getName(), rhs.getName());
    }
};

#endif //LODESTONE_NAMESPACEDSTRING_H