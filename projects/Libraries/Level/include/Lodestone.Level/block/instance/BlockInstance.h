//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKSTATE_H
#define LODESTONE_BLOCKSTATE_H

#include "Lodestone.Level/block/BlockRegistry.h"
#include "Lodestone.Level/properties/AbstractProperty.h"
#include <gtl/phmap.hpp>
#include <string>

namespace lodestone::level::block {
    class Block;
}

namespace lodestone::level::block::instance {
    /** Wraps a block with runtime-modifiable properties */
    class LODESTONE_LEVEL_API BlockInstance
        : public lodestone::common::string::StringSerializable {
      public:
        static const map_t<common::registry::Identifier, level::properties::AbstractProperty *>
            EMPTY_PROPERTIES;

        BlockInstance(const Block *block) : m_block(block) {};

        ~BlockInstance() override;

        explicit BlockInstance(const common::registry::Identifier *id)
            : BlockInstance(BlockRegistry::getInstance().getBlock(id)) {};

        BlockInstance() : BlockInstance(BlockRegistry::s_defaultBlock) {}

        const map_t<common::registry::Identifier, level::properties::AbstractProperty *> &
        getProperties() const;

        virtual bool hasProperty(const common::registry::Identifier &id) const;

        virtual const level::properties::AbstractProperty *
        getProperty(const common::registry::Identifier &id) const;

        const Block *getBlock() const { return m_block; }

        virtual void setProperty(const common::registry::Identifier &id,
                                 level::properties::AbstractProperty *property);

        virtual const level::properties::AbstractProperty *
        operator[](const common::registry::Identifier &id) const;

        bool operator==(const BlockInstance &b) const {
            return m_block == b.m_block && m_properties == b.m_properties;
        }

        std::string toString() const override {
            if (this->m_block)
                return std::format("BlockInstance[block={}]",
                                   m_block->getID()->getString());

            return "BlockInstance";
        };

      private:
        const Block *m_block;
        map_t<common::registry::Identifier, level::properties::AbstractProperty *> *m_properties =
            nullptr;
    };
} // namespace lodestone::level::block::properties

#endif // LODESTONE_BLOCKSTATE_H