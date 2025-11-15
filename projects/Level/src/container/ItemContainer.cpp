//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Level/container/ItemContainer.h"

namespace lodestone {
    namespace level {
        namespace container {
            ItemContainer::ItemContainer(const int count) : mCount(count), mSlots(new std::unique_ptr<item::ItemProperties>[count]){
            }

            ItemContainer::~ItemContainer() {
                delete[] mSlots;
            }

            int ItemContainer::getCount() const {
                return mCount;
            }

            const item::ItemProperties * ItemContainer::getItems() const {
                return mSlots->get();
            }

            item::ItemProperties * ItemContainer::getItem(const int slot) const {
                if (slot > mCount || 0 > slot) return nullptr;

                return mSlots[slot].get();
            }

            void ItemContainer::setItem(const int slot, std::unique_ptr<item::ItemProperties> item) const {
                if (slot > mCount || 0 > slot) return;

                mSlots[slot] = std::move(item);
            }

            bool ItemContainer::slotHasItem(const int slot) const {
                if (slot > mCount || 0 > slot) return false;

                return mSlots[slot] != nullptr;
            }
        } // player
    } // level
} // lodestone