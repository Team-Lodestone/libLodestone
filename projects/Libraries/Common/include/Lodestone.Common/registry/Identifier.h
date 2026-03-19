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
            : m_namespace("lodestone"), m_path(name) {};

      public:
        constexpr Identifier(const char *_namespace, const char *path) noexcept
            : m_namespace(_namespace), m_path(path) {};

        constexpr const char *getPath() const noexcept { return m_path; }

        constexpr const char *getNamespace() const noexcept {
            return m_namespace;
        }

        constexpr std::string getString() const noexcept {
            return std::string(m_namespace) + ":" + m_path;
        }

        std::string toString() const override { return getString(); };

        constexpr bool operator==(const Identifier &rhs) const noexcept {
            return util::Util::strcmpConstexpr(this->m_path, rhs.m_path) &&
                   util::Util::strcmpConstexpr(this->m_namespace,
                                               rhs.m_namespace);
        }

        constexpr operator std::string() const noexcept {
            return getString();
        }

        constexpr friend std::ostream &
        operator<<(std::ostream &os, const Identifier &s) noexcept {
            os << s.getString();
            return os;
        }

      private:
        const char *m_namespace;
        const char *m_path;
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

template <>
struct std::hash<lodestone::common::registry::Identifier> {
    size_t operator()(
        const lodestone::common::registry::Identifier &s) const noexcept {
        return std::hash<std::string_view>{}(s.getPath()) ^
               (std::hash<std::string_view>{}(s.getNamespace()) << 1);
    }
};

#endif // LODESTONE_NAMESPACEDSTRING_H