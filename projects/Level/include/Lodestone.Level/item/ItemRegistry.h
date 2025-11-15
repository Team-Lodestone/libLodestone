//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEMREGISTRY_H
#define LODESTONE_ITEMREGISTRY_H
#include <unordered_map>

#include <Lodestone.Common/Defines.h>

#include <gtl/phmap.hpp>
#include "Lodestone.Level/item/Item.h"
#include "Lodestone.Level/item/Items.h"

namespace lodestone::level::item {
    class LODESTONE_API ItemRegistry {
    protected:
        ItemRegistry() = default;

    public:
#define REGISTER_ITEM(n) {n, new Item(n)}

        static const Item *sDefaultItem;

        static ItemRegistry& getInstance() {
            static ItemRegistry sInstance;
            return sInstance;
        }

        void registerItem(const lodestone::common::registry::Identifier *id, const Item *item);

        // couldn't come up with a better name
        bool registerItemIfNonExistent(const lodestone::common::registry::Identifier *id,
                                        const Item *item) noexcept;

        const Item *getItem(const lodestone::common::registry::Identifier *id) const;

        const Item *operator[](const lodestone::common::registry::Identifier *id) const;

        gtl::flat_hash_map<const lodestone::common::registry::Identifier *, const Item *>::iterator begin() {
            return mItems.begin();
        }

        gtl::flat_hash_map<const lodestone::common::registry::Identifier *, const Item *>::iterator end() {
            return mItems.end();
        }

    private:
        gtl::flat_hash_map<const lodestone::common::registry::Identifier *, const Item *> mItems = {
            REGISTER_ITEM(&Items::NONE)
        };
    };
}

#endif //LODESTONE_ITEMREGISTRY_H