//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef LODESTONE_ImmutableBlockInstance_H
#define LODESTONE_ImmutableBlockInstance_H
#include "Lodestone.Level/block/instance/BlockInstance.h"

namespace lodestone::level::block::instance {
    /** Block properties type that cannot be written to  */
    class ImmutableBlockInstance : public BlockInstance {
      private:
        ImmutableBlockInstance();

      public:
        static ImmutableBlockInstance *getInstance();

        bool hasProperty(const common::registry::Identifier &id) const override;

        const level::properties::AbstractProperty *
        getProperty(const common::registry::Identifier &id) const override;

        void
        setProperty(const common::registry::Identifier &id,
                    level::properties::AbstractProperty *property) override;

        const level::properties::AbstractProperty *
        operator[](const common::registry::Identifier &id) const override;
    };
} // namespace lodestone::level::block::properties

#endif // LODESTONE_ImmutableBlockInstance_H
