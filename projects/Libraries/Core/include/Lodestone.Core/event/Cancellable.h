/** @file Cancellable.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_CANCELLABLE_H
#define LODESTONE_CANCELLABLE_H

namespace lodestone::core::event {
  struct Cancellable {
    bool cancelled;
  };
}

#endif // LODESTONE_CANCELLABLE_H