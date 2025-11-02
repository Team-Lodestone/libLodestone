//
// Created by DexrnZacAttack on 10/17/25 using zPc-i2.
//
#ifndef LODESTONE_NAMESPACEDSTRING_H
#define LODESTONE_NAMESPACEDSTRING_H
#include <format>

// this class required me to upgrade to c++20
namespace lodestone::level::registry {
    class NamespacedString {
    protected:
        constexpr NamespacedString(const char *name) noexcept : mNamespace("lodestone"), mName(name) {};
    public:
        constexpr NamespacedString(const char *nmsp, const char *name) noexcept : mNamespace(nmsp), mName(name) {};

        constexpr const char *getName() const noexcept {
            return mName;
        }

        constexpr const char *getNamespace() const noexcept {
            return mNamespace;
        }

        constexpr std::string getString() const noexcept {
            return std::format("{}:{}", mNamespace, mName);
        };

        constexpr operator std::string() const noexcept {
            return getString();
        }

        constexpr friend std::ostream& operator<<(std::ostream& os, const NamespacedString& s) {
            os << s.getString();
            return os;
        }

    private:
        const char *const mNamespace;
        const char *const mName;
    };
}

template <>
struct std::formatter<lodestone::level::registry::NamespacedString> : formatter<string> {
    std::format_context::iterator format(const lodestone::level::registry::NamespacedString &s, format_context &c) const {
        return formatter<string>::format(s.getString(), c);
    }
};

#endif //LODESTONE_NAMESPACEDSTRING_H
