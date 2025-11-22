//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEMCONTAINER_H
#define LODESTONE_ITEMCONTAINER_H
#include <memory>

#include "Lodestone.Level/item/Item.h"
#include "Lodestone.Level/item/ItemProperties.h"

namespace lodestone::level::container {
    class ItemContainer {
      public:
        explicit ItemContainer(int count = 35);
        ~ItemContainer();

        int getCount() const;

        const item::ItemProperties *getItems() const;

        item::ItemProperties *getItem(int slot) const;
        void setItem(int slot,
                     std::unique_ptr<item::ItemProperties> item) const;
        bool slotHasItem(int slot) const;

      private:
        int mCount;
        std::unique_ptr<item::ItemProperties> *mSlots;
    };
} // namespace lodestone::level::container

#endif // LODESTONE_ITEMCONTAINER_H
