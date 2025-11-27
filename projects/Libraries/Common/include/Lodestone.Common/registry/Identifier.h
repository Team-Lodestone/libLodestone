//
// Created by DexrnZacAttack on 10/17/25 using zPc-i2.
//
#ifndef LODESTONE_NAMESPACEDSTRING_H
#define LODESTONE_NAMESPACEDSTRING_H
#include "Lodestone.Common/string/StringSerializable.h"
#include <cstring>
#include <format>

#include "Lodestone.Common/util/Math.h"

// this class required me to upgrade to c++20
namespace lodestone::common::registry {
    class Identifier : public string::StringSerializable {
      protected:
        explicit constexpr Identifier(const char *name) noexcept
            : mNamespace("lodestone"), mName(name) {};

      public:
        constexpr Identifier(const char *nmsp, const char *name) noexcept
            : mNamespace(nmsp), mName(name) {};

        constexpr const char *getName() const noexcept { return mName; }

        constexpr const char *getNamespace() const noexcept {
            return mNamespace;
        }

        constexpr std::string getString() const noexcept {
            return std::string(mNamespace) + ":" + mName;
        }

        constexpr std::string toString() const override { return getString(); };

        constexpr bool operator==(const Identifier &rhs) const noexcept {
            return util::Math::strcmpConstexpr(this->mName, rhs.mName) &&
                   util::Math::strcmpConstexpr(this->mNamespace,
                                               rhs.mNamespace);
        }

        constexpr operator std::string() const noexcept override {
            return getString();
        }

        constexpr friend std::ostream &
        operator<<(std::ostream &os, const Identifier &s) noexcept {
            os << s.getString();
            return os;
        }

      private:
        const char *mNamespace;
        const char *mName;
    };
} // namespace lodestone::common::registry

template <>
struct std::formatter<lodestone::common::registry::Identifier>
    : formatter<string> {
    std::format_context::iterator
    format(const lodestone::common::registry::Identifier &s,
           format_context &c) const {
        return formatter<string>::format(s.getString(), c);
    }
};

struct IdentifierHasher {
    size_t operator()(
        const lodestone::common::registry::Identifier &s) const noexcept {
        return std::hash<std::string_view>{}(s.getName()) ^
               (std::hash<std::string_view>{}(s.getNamespace()) << 1);
    }
};

struct IdentifierComparator {
    bool operator()(
        const lodestone::common::registry::Identifier &lhs,
        const lodestone::common::registry::Identifier &rhs) const noexcept {
        return !std::strcmp(lhs.getNamespace(), rhs.getNamespace()) &&
               !std::strcmp(lhs.getName(), rhs.getName());
    }
};

#endif // LODESTONE_NAMESPACEDSTRING_H