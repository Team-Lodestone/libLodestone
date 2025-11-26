//
// Created by DexrnZacAttack on 11/25/25 using zPc-i2.
//
#ifndef LODESTONE_OPTIONALTEMPLATEDPROPERTY_H
#define LODESTONE_OPTIONALTEMPLATEDPROPERTY_H
#include "Lodestone.Level/properties/TemplatedProperty.h"

template <typename T>
using OptionalTemplatedProperty = lodestone::level::properties::TemplatedProperty<std::optional<T>>;

#endif // LODESTONE_OPTIONALTEMPLATEDPROPERTY_H