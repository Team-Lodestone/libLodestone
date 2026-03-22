//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKREGISTRY_H
#define LODESTONE_BLOCKREGISTRY_H
#include "Lodestone.Common/event/Event.h"

#include <unordered_map>

#include "Lodestone.Level/internal/Exports.h"

#include "Lodestone.Level/block/Block.h"
#include "Lodestone.Level/block/Blocks.h"
#include <gtl/phmap.hpp>

namespace lodestone::level::block {
    class LODESTONE_LEVEL_API BlockRegistry {
      protected:
        BlockRegistry();

      public:
#define REGISTER_BLOCK(n, m, d) {n, new lodestone::level::block::Block(n, m, d)}
#define REGISTER_DERIVED_BLOCK(n, m, d, f) {n, new f(n, m, d)}
#define REGISTER_BLOCK_FUNC(n, m, d) registerBlock(n, new lodestone::level::block::Block(n, m, d))
#define REGISTER_DERIVED_BLOCK_FUNC(n, m, d, f) registerBlock(n, new f(n, m, d))

        static const Block *s_defaultBlock;

        static BlockRegistry &getInstance();

        void registerBlock(const lodestone::common::registry::Identifier *id,
                           const Block *block);

        // couldn't come up with a better name
        bool registerBlockIfNonExistent(
            const lodestone::common::registry::Identifier *id,
            const Block *block) noexcept;

        const Block *
        getBlock(const lodestone::common::registry::Identifier *id) const;

        const Block *
        operator[](const lodestone::common::registry::Identifier *id) const;

        map_t<const lodestone::common::registry::Identifier *,
              const Block *>::iterator
        begin() {
            return m_blocks.begin();
        }

        map_t<const lodestone::common::registry::Identifier *,
              const Block *>::iterator
        end() {
            return m_blocks.end();
        }

        common::event::Event<const lodestone::common::registry::Identifier *, const Block *> blockRegisteredEvent;
      private:
        map_t<const lodestone::common::registry::Identifier *, const Block *>
            m_blocks;
    };
} // namespace lodestone::level::block

#endif // LODESTONE_BLOCKREGISTRY_H