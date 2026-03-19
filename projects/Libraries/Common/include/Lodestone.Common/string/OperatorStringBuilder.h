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

namespace lodestone::common::string {
    // we have Apache ToStringBuilder at home.
    class OperatorStringBuilder {
      public:
        OperatorStringBuilder(const std::type_info &type) : m_type(type) {
            const std::string d = demangle(type.name());
            m_stream << d.substr(d.find_last_of(':') + 1) << "[";
        };

        template <typename T>
        constexpr OperatorStringBuilder *addField(const std::string &name,
                                                  const T &v) {
            m_stream << name << "=" << v << ", ";
            return this;
        }

        constexpr std::string toString() {
            std::string s = m_stream.str();
            if (!s.empty() && s.ends_with(", ")) {
                // substr probs creates new string
                // so this should be more efficient
                s.pop_back();
                s.pop_back();
            }

            m_stream.str("");
            m_stream << s << "]";

            return m_stream.str();
        };

#define ADD_FIELD(name) addField(#name, name)

        // TODO: breaks on windows
        static constexpr const char *demangle(const char *name) {
#if defined(__GNUC__) || defined(__clang__)
            int err = 0;
            char *demangled = abi::__cxa_demangle(name, nullptr, nullptr, &err);

            if (!err)
                return demangled;

            free(demangled);
            return name;
#else
            return name;
#endif
        }

        constexpr operator std::string() { return toString(); }

      private:
        const std::type_info &m_type;
        std::ostringstream m_stream;
    };
} // namespace lodestone::common::string