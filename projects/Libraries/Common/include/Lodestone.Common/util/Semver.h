/** @file Semver.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_SEMVER_H
#define LODESTONE_SEMVER_H
#include <optional>
#include <string>

namespace lodestone::common::util {
    /** Rough impl of a Semver class, if you can even call it that... hardly follows the specification lmao
     *
     * Does what we need it to do though.
     */
    struct Semver {
        static constexpr int NONE = -1;

        constexpr std::string toString() const {
            std::string ver = std::to_string(major) +
                              "." + std::to_string(minor) +
                              "." + std::to_string(patch);

            if (devVer != NONE) {
                ver += "-dev." + std::to_string(devVer);
            }

            return ver;
        }

        explicit constexpr operator std::string() const {
            return this->toString();
        }

        const int major;
        const int minor;
        const int patch;
        const int devVer;
    };
} // util
// app
// lodestone

#endif // LODESTONE_SEMVER_H