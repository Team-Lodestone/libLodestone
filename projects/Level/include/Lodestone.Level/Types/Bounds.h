//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_BOUNDS_H
#define LODESTONE_BOUNDS_H

#include <Lodestone.Common/Lodestone.h>
#include "Lodestone.Level/Types/Vec3i.h"

namespace lodestone::level::types {
    struct LODESTONE_API Bounds {
        Vec3i min;
        Vec3i max;

        bool operator==(const Bounds &rhs) const {
            return min == rhs.min
                && max == rhs.max;
        }

        Bounds operator+(const int v) const {
            return {
                min + v,
                max + v
            };
        }

        Bounds operator-(const int v) const {
            return {
                min - v,
                max - v
            };
        }

        Bounds operator*(const int v) const {
            return {
                min * v,
                max * v
            };
        }

        Bounds operator/(const int v) const {
            return {
                min / v,
                max / v
            };
        }

        Bounds operator+(const Bounds &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        Bounds operator-(const Bounds &rhs) const {
            return {
                rhs.min - min,
                rhs.max - max
            };
        }


        Bounds operator*(const Bounds &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        Bounds operator/(const Bounds &rhs) const {
            return {
                rhs.min / min,
                rhs.max / max
            };
        }
    };
}

#endif //LODESTONE_BOUNDS_H