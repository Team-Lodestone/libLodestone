/** @file Cancellable.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_CANCELLABLE_H
#define LODESTONE_CANCELLABLE_H

namespace lodestone::core::event {
  struct Cancellable {
    bool cancelled;
  };
}

#endif // LODESTONE_CANCELLABLE_H