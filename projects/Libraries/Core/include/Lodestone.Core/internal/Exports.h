/** @file Exports.h
 *
 * @author DexrnZacAttack
 * @date 3/21/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_CORE_EXPORTS_H
#define LODESTONE_CORE_EXPORTS_H

#ifdef __EMSCRIPTEN__
#   define LODESTONE_CORE_API
#   define NO_DISCARD __attribute__((used))
#elif defined(LODESTONE_CORE_EXPORTS)
#   if defined(__GNUC__) || defined(__clang__)
#       define NO_DISCARD __attribute__((used))
#       define LODESTONE_CORE_API __attribute__((visibility("default")))
#   else
#       define NO_DISCARD __declspec(noinline)
#       define LODESTONE_CORE_API __declspec(dllexport)
#   endif
#else
#   if defined(__GNUC__) || defined(__clang__)
#       define NO_DISCARD __attribute__((used))
#       define LODESTONE_CORE_API __attribute__((visibility("default")))
#   else
#       define NO_DISCARD __declspec(noinline)
#       define LODESTONE_CORE_API __declspec(dllimport)
#   endif
#endif

#endif // LODESTONE_CORE_EXPORTS_H