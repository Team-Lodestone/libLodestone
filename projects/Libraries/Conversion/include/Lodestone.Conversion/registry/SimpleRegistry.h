//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_SIMPLEREGISTRY_H
#define LODESTONE_SIMPLEREGISTRY_H

#include <Lodestone.Common/event/Event.h>

#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/registry/Identifier.h>

#include <Lodestone.Common/registry/Identifiable.h>

#include <Lodestone.Common/util/Logging.h>
#include <stdexcept>
#include <format>

namespace lodestone::conversion::registry {
    template <const common::registry::Identifier *Identifier, typename Type, typename Stored = std::unique_ptr<const Type>>
    class LODESTONE_API SimpleRegistry : public common::registry::Identifiable<Identifier> {
    protected:
        SimpleRegistry() = default;
    public:
        //hopefully this will save more than the hours of debugging that I spent
        SimpleRegistry(SimpleRegistry &rhs) = delete;

        void put(const common::registry::Identifier &id,
                         Stored io);

        const Type *get(common::registry::Identifier id) const;

        template <typename R>
        requires std::is_base_of_v<Type, R>
        const R *getAs(common::registry::Identifier id) const;

        template <typename R>
        requires std::is_base_of_v<Type, R>
              && std::is_base_of_v<common::registry::IIdentifiable, R>
        const R *getOfType() const;


        common::event::Event<common::registry::Identifier> objectRegisteredEvent;
    private:
        map_t<common::registry::Identifier,
            Stored>
            m_registry;
    };

#include "Lodestone.Conversion/registry/SimpleRegistry.tpp"
}

#endif // LODESTONE_SIMPLEREGISTRY_H