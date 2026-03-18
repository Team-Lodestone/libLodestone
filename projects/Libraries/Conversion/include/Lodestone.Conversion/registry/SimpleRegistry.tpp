//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_SIMPLEREGISTRY_TPP
#define LODESTONE_SIMPLEREGISTRY_TPP

template <const common::registry::Identifier *Identifier, typename Type, typename Stored>
void SimpleRegistry<Identifier, Type, Stored>::put(const common::registry::Identifier &id, Stored io) {
    if (this->m_registry.contains(id))
        throw std::runtime_error(
            std::format("{} '{}' is already registered", Identifier->getString(), id));

    this->m_registry[id] = std::move(io);

    // LOG_DEBUG("Registered " << Identifier->getString() << " '" << id << "'");
    objectRegisteredEvent.notify(id);
}

template <const common::registry::Identifier *Identifier, typename Type, typename Stored>
const Type *SimpleRegistry<Identifier, Type, Stored>::get(common::registry::Identifier id) const {
    if (const auto it = m_registry.find(id);
    it != m_registry.end())
        return it->second.get();

    LOG_DEBUG("Attempted to get value from nonexistent key '" << Identifier->getString() << "'");
    return nullptr;
}

template <const common::registry::Identifier *Identifier, typename Type, typename Stored>
template<typename R>
requires std::is_base_of_v<Type, R>
const R *SimpleRegistry<Identifier, Type, Stored>::getAs(const common::registry::Identifier id) const {
    return dynamic_cast<R *>(this->get(id));
}

template <const common::registry::Identifier *Identifier, typename Type, typename Stored>
template<typename R> requires std::is_base_of_v<Type, R>
                           && std::is_base_of_v<common::registry::IIdentifiable, R>
const R * SimpleRegistry<Identifier, Type, Stored>::getOfType() const {
    return this->getAs<R>(*R::getIdentifier());
}

#endif // LODESTONE_SIMPLEREGISTRY_TPP
