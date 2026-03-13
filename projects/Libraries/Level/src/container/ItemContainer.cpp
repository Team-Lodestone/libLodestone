//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Level/container/ItemContainer.h"

namespace lodestone::level::container {
    ItemContainer::ItemContainer(const int count)
        : m_count(count),
          m_slots(new std::unique_ptr<item::ItemInstance>[count]) {}

    ItemContainer::~ItemContainer() { delete[] m_slots; }

    int ItemContainer::getCount() const { return m_count; }

    const item::ItemInstance *ItemContainer::getItems() const {
        return m_slots->get();
    }

    item::ItemInstance *ItemContainer::getItem(const int slot) const {
        if (slot > m_count || 0 > slot)
            return nullptr;

        return m_slots[slot].get();
    }

    void
    ItemContainer::setItem(const int slot,
                           std::unique_ptr<item::ItemInstance> item) const {
        if (slot > m_count || 0 > slot)
            return;

        m_slots[slot] = std::move(item);
    }

    bool ItemContainer::slotHasItem(const int slot) const {
        if (slot > m_count || 0 > slot)
            return false;

        return m_slots[slot] != nullptr;
    }
} // namespace lodestone::level::container