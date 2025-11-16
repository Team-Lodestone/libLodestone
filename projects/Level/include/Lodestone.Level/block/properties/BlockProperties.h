//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKSTATE_H
#define LODESTONE_BLOCKSTATE_H

#include <gtl/phmap.hpp>
#include "Lodestone.Level/block/BlockRegistry.h"
#include "Lodestone.Level/properties/AbstractProperty.h"
#include <string>

namespace lodestone::level::block {
    class Block;
}

namespace lodestone::level::block::properties {
    /** Wraps a block with runtime-modifiable properties */
    class BlockProperties : public lodestone::common::string::StringSerializable {
    public:
        static const gtl::flat_hash_map<std::string, level::properties::AbstractProperty *> EMPTY_PROPERTIES;

        BlockProperties(const Block *block) : mBlock(block) {
        };

        ~BlockProperties() override;

        explicit BlockProperties(const common::registry::Identifier *id) : mBlock(
            BlockRegistry::getInstance().getBlock(id)) {
        };

        BlockProperties() : mBlock(BlockRegistry::sDefaultBlock) {
        }

// TODO add destructor back for some reason it throws some stupid error right now

        const gtl::flat_hash_map<std::string, level::properties::AbstractProperty *> &getProperties() const;

        virtual bool hasProperty(const std::string &id) const;

        virtual const level::properties::AbstractProperty *getProperty(const std::string &id) const;

        virtual level::properties::AbstractProperty *getProperty(const std::string &id);

        const Block *getBlock() const { return mBlock; }

        virtual void setProperty(const std::string &id, level::properties::AbstractProperty * property);

        virtual const level::properties::AbstractProperty *operator[](const std::string &id) const;

        virtual level::properties::AbstractProperty *operator[](const std::string &id);

        bool operator==(const BlockProperties &b) const {
            return mBlock == b.mBlock && mProperties == b.mProperties;
        }

        constexpr std::string toString() const override {
            return std::format("BlockProperties[block={}]", mBlock->getID()->getString());
        };

    private:
        const Block *mBlock;
        gtl::flat_hash_map<std::string, level::properties::AbstractProperty*> *mProperties = nullptr;
    };
}

#endif //LODESTONE_BLOCKSTATE_H