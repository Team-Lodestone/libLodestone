#include "Lodestone.Level/item/ItemRegistry.h"

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
        static ItemRegistry sInstance;
        return sInstance;
    }

    void ItemRegistry::registerItem(
        const lodestone::common::registry::Identifier *id, const Item *item) {
        if (mItems.contains(id))
            throw std::runtime_error(
                std::format("Item '{}' is already registered", *id));

        mItems[id] = std::move(item);
#if CMAKE_BUILD_DEBUG
        std::cout << "Registered item '" << *id << "'" << std::endl;
#endif
    }

    bool ItemRegistry::registerItemIfNonExistent(
        const lodestone::common::registry::Identifier *id,
        const Item *item) noexcept {
        if (mItems.contains(id))
            return false;

        mItems[id] = std::move(item);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered item '" << *id << "'" << std::endl;
#endif

        return true;
    }

    const Item *ItemRegistry::getItem(
        const lodestone::common::registry::Identifier *id) const {
        if (const auto it = mItems.find(id); it != mItems.end())
            return it->second;

        return nullptr;
    }

    const Item *ItemRegistry::operator[](
        const lodestone::common::registry::Identifier *id) const {
        return getItem(id);
    }
} // namespace lodestone::level::item