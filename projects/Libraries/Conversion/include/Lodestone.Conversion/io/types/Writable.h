//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_WRITABLE_H
#define LODESTONE_WRITABLE_H

namespace lodestone::conversion::io::types {
    template <typename W, typename WO = void, typename WR = void>
    class Writable {
    public:
        virtual ~Writable() = default;

        virtual WR write(W obj, WO& options) const = 0;
    };
}

#endif // LODESTONE_WRITABLE_H
