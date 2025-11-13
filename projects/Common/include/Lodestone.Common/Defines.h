//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once

#ifdef __EMSCRIPTEN__
#define LODESTONE_API
#define NO_DISCARD __attribute__((used))
#elif defined(LODESTONE_EXPORTS)
#if defined(__GNUC__) || defined(__clang__)
#define NO_DISCARD __attribute__((used))
#define LODESTONE_API __attribute__((visibility("default")))
#else
#define NO_DISCARD __declspec(noinline)
#define LODESTONE_API __declspec(dllexport)
#endif
#else
#if defined(__GNUC__) || defined(__clang__)
#define NO_DISCARD __attribute__((used))
#define LODESTONE_API __attribute__((visibility("default")))
#else
#define NO_DISCARD __declspec(noinline)
#define LODESTONE_API __declspec(dllimport)
#endif
#endif

#if defined(_MSC_VER)
#define TO_SECTION(n) __pragma(section(n, read)) __declspec(allocate(n))
#elif defined(__GNUC__) || defined(__clang__)
#define TO_SECTION(n) __attribute__((section(n)))
#endif

#if CMAKE_BUILD_DEBUG
#define LODESTONE_BUILD_TYPE "Debug"
#else
#define LODESTONE_BUILD_TYPE "Release"
#endif

// you're telling me they couldn't have come up with some neat way to cast between unique_ptr types?
#define CAST_UNIQUE_PTR(to, var) std::unique_ptr<to>(static_cast<to *>(var.release()));