#include "Lodestone.Level/item/ItemRegistry.h"

#include <Lodestone.Common/util/Logging.h>

#if CMAKE_BUILD_DEBUG
#include <iostream>
#endif
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::item {
    const Item *ItemRegistry::sDefaultItem =
        getInstance().getItem(&Items::NONE);

    ItemRegistry &ItemRegistry::getInstance() {
        static ItemRegistry s_instance;
        return s_instance;
    }

    void ItemRegistry::registerItem(
        const lodestone::common::registry::Identifier *id, const Item *item) {
        if (m_items.contains(id))
            throw std::runtime_error(
                std::format("Item '{}' is already registered", *id));

        m_items[id] = item;
        // LOG_DEBUG("Registered item '" << *id << "'");

        this->itemRegisteredEvent.notify(id, item);
    }

    bool ItemRegistry::registerItemIfNonExistent(
        const lodestone::common::registry::Identifier *id,
        const Item *item) noexcept {
        if (m_items.contains(id))
            return false;

        m_items[id] = item;

        // LOG_DEBUG("Registered item '" << *id << "'");
        this->itemRegisteredEvent.notify(id, item);

        return true;
    }

    const Item *ItemRegistry::getItem(
        const lodestone::common::registry::Identifier *id) const {
        if (const auto it = m_items.find(id); it != m_items.end())
            return it->second;

        return nullptr;
    }

    const Item *ItemRegistry::operator[](
        const lodestone::common::registry::Identifier *id) const {
        return getItem(id);
    }
} // namespace lodestone::level::item