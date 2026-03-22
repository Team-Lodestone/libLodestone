//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#include <gtl/phmap.hpp>

#if defined(_MSC_VER)
#define TO_SECTION(n) __pragma(section(n, read)) __declspec(allocate(n))
#elif defined(__GNUC__) || defined(__clang__)
#define TO_SECTION(n) __attribute__((section(n)))
#endif

// you're telling me they couldn't have come up with some neat way to cast
// between unique_ptr types?
#define CAST_UNIQUE_PTR(to, var)                                               \
    std::unique_ptr<to>(static_cast<to *>(var.release()));

typedef long signed int signed_size_t;

template <typename... T>
#ifdef CMAKE_BUILD_DEBUG
using map_t = std::unordered_map<T...>; // so we can inspect in debugger
#else
using map_t = gtl::flat_hash_map<T...>;
#endif