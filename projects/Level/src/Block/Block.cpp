//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Block/Block.h"

namespace lodestone::level::block {
    std::string Block::toString() const {
        return (new OperatorStringBuilder(typeid(*this)))
            ->ADD_FIELD(mId)
            ->toString();
    }
}
