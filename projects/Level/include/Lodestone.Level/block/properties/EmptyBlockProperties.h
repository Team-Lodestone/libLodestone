//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYBLOCKPROPERTIES_H
#define LODESTONE_EMPTYBLOCKPROPERTIES_H
#include "Lodestone.Level/block/properties/BlockProperties.h"

namespace lodestone::level::block::properties {
    /** Block properties type that cannot be written to  */
    class EmptyBlockProperties : public BlockProperties {
      private:
        EmptyBlockProperties();

      public:
        static EmptyBlockProperties *getInstance();

        bool hasProperty(const std::string &id) const override;

        const level::properties::AbstractProperty *
        getProperty(const std::string &id) const override;

        level::properties::AbstractProperty *
        getProperty(const std::string &id) override;

        void
        setProperty(const std::string &id,
                    level::properties::AbstractProperty *property) override;

        const level::properties::AbstractProperty *
        operator[](const std::string &id) const override;

        level::properties::AbstractProperty *
        operator[](const std::string &id) override;
    };
} // namespace lodestone::level::block::properties

#endif // LODESTONE_EMPTYBLOCKPROPERTIES_H
