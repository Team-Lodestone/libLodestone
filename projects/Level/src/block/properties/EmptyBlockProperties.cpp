//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "Lodestone.Level/block/properties/EmptyBlockProperties.h"

namespace lodestone {
    namespace level {
        namespace block {
            namespace properties {
                EmptyBlockProperties::EmptyBlockProperties() : BlockProperties(BlockRegistry::sDefaultBlock) {
                }

                EmptyBlockProperties * EmptyBlockProperties::getInstance() {
                    static EmptyBlockProperties sInstance;
                    return &sInstance;
                }

                bool EmptyBlockProperties::hasProperty(const std::string &id) const {
                    return false;
                }

                const level::properties::AbstractProperty * EmptyBlockProperties::getProperty(
                    const std::string &id) const {
                    return nullptr;
                }

                level::properties::AbstractProperty * EmptyBlockProperties::getProperty(const std::string &id) {
                    return nullptr;
                }

                void EmptyBlockProperties::setProperty(const std::string &id,
                    level::properties::AbstractProperty *property) {
                }

                const level::properties::AbstractProperty * EmptyBlockProperties::operator[](
                    const std::string &id) const {
                    return nullptr;
                }

                level::properties::AbstractProperty * EmptyBlockProperties::operator[](const std::string &id) {
                    return nullptr;
                }
            } // properties
        } // block
    } // level
} // lodestone