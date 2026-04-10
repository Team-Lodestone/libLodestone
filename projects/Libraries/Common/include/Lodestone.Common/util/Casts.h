/** @file Casts.h
 *
 * @author DexrnZacAttack
 * @date 4/6/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_CASTS_H
#define LODESTONE_CASTS_H
#include <memory>

namespace lodestone::common::util {
    class Casts {
    public:
        template <typename To, typename From>
        static std::unique_ptr<To> static_unique_pointer_cast(std::unique_ptr<From> ptr) {
            To *p = static_cast<To *>(ptr.release());

            return std::unique_ptr<To>(p);
        }

        template <typename To, typename From>
        static std::unique_ptr<To> dynamic_unique_pointer_cast(std::unique_ptr<From> ptr) {
            To *p = dynamic_cast<To *>(ptr.release());

            return std::unique_ptr<To>(p);
        }
    };
}

#endif // LODESTONE_CASTS_H