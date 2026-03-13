//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEMCONTAINER_H
#define LODESTONE_ITEMCONTAINER_H
#include <memory>

#include "Lodestone.Level/item/Item.h"
#include "Lodestone.Level/item/ItemInstance.h"

namespace lodestone::level::container {
    class ItemContainer {
      public:
        explicit ItemContainer(int count = 35);
        ~ItemContainer();

        int getCount() const;

        const item::ItemInstance *getItems() const;

        item::ItemInstance *getItem(int slot) const;
        void setItem(int slot,
                     std::unique_ptr<item::ItemInstance> item) const;
        bool slotHasItem(int slot) const;

        bool operator==(const ItemContainer &rhs) const {
            if (this->m_count != rhs.m_count)
                return false;

            for (size_t i = 0; i < m_count; ++i) {
                const std::unique_ptr<item::ItemInstance>& a = m_slots[i];
                const std::unique_ptr<item::ItemInstance>& b = rhs.m_slots[i];

                if (a && b) {
                    if (*a != *b) return false;
                } else if (!a && !b) {
                    continue;
                } else {
                    return false;
                }
            }

            return true;
        }

      private:
        int m_count;
        std::unique_ptr<item::ItemInstance> *m_slots;
    };
} // namespace lodestone::level::container

namespace std {
    template <>
    struct hash<lodestone::level::container::ItemContainer> {
        size_t operator()(
            const lodestone::level::container::ItemContainer &s) const noexcept {
            return std::hash<int>{}(s.getCount())
                 ^ std::hash<const lodestone::level::item::ItemInstance *>{}(s.getItems()) << 8;
        }
    };
}

#endif // LODESTONE_ITEMCONTAINER_H
