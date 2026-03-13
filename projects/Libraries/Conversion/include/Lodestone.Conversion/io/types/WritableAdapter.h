//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_WRITABLEADAPTER_H
#define LODESTONE_WRITABLEADAPTER_H

namespace lodestone::conversion::io::types {
    class WritableAdapter {
    public:
        virtual ~WritableAdapter() = default;

        virtual void baseWrite(void *obj, void *options) const = 0;
    };
}

#endif // LODESTONE_WRITABLEADAPTER_H
