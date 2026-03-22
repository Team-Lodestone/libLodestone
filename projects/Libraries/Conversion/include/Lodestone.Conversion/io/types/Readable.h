//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_READABLE_H
#define LODESTONE_READABLE_H

namespace lodestone::conversion::io::types {
    template <typename R, typename RO = void>
    class LODESTONE_CONVERSION_API Readable {
    public:
        virtual ~Readable() = default;

        virtual R read(RO& options) const = 0;
    };
}

#endif // LODESTONE_READABLE_H
