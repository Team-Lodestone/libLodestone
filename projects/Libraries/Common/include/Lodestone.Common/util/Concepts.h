//
// Created by DexrnZacAttack on 2/15/26 using zPc-i2.
//
#ifndef LODESTONE_CONCEPTS_H
#define LODESTONE_CONCEPTS_H
#include <concepts>
#include <type_traits>

namespace lodestone::common::util::concepts {
    template <typename Base, typename Type>
    concept void_or_derived_from_v = std::is_void_v<Type> || std::is_base_of_v<Base, Type>;
}

#endif // LODESTONE_CONCEPTS_H