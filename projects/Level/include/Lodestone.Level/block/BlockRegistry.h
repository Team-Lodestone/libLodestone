//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKREGISTRY_H
#define LODESTONE_BLOCKREGISTRY_H
#include <unordered_map>

#include <Lodestone.Common/Defines.h>

#include <gtl/phmap.hpp>
#include "Lodestone.Level/block/Block.h"
#include "Lodestone.Level/block/Blocks.h"

namespace lodestone::level::block {
    class LODESTONE_API BlockRegistry {
    protected:
        BlockRegistry();

    public:
#define REGISTER_BLOCK(n, m) {n, new Block(n, m)}
#define REGISTER_BLOCK_FUNC(n, m) registerBlock(n, new Block(n, m))

        static const Block *sDefaultBlock;

        static BlockRegistry& getInstance();

        void registerBlock(const lodestone::common::registry::Identifier *id, const Block *block);

        // couldn't come up with a better name
        bool registerBlockIfNonExistent(const lodestone::common::registry::Identifier *id,
                                        const Block *block) noexcept;

        const Block *getBlock(const lodestone::common::registry::Identifier *id) const;

        const Block *operator[](const lodestone::common::registry::Identifier *id) const;

        gtl::flat_hash_map<const lodestone::common::registry::Identifier *, const Block *>::iterator begin() {
            return mBlocks.begin();
        }

        gtl::flat_hash_map<const lodestone::common::registry::Identifier *, const Block *>::iterator end() {
            return mBlocks.end();
        }

    private:
        gtl::flat_hash_map<const lodestone::common::registry::Identifier *, const Block *> mBlocks;
    };
}

#endif //LODESTONE_BLOCKREGISTRY_H