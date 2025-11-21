#include "Lodestone.Level/block/BlockRegistry.h"

#include "Lodestone.Level/item/ItemRegistry.h"

#if CMAKE_BUILD_DEBUG
#include <iostream>
#endif
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    const Block *BlockRegistry::sDefaultBlock =
        getInstance().getBlock(&Blocks::AIR);

    BlockRegistry::BlockRegistry() {
        REGISTER_BLOCK_FUNC(&Blocks::AIR, material::Material({0, 0, 0, 0}));
        // TODO make Minecraft project which just initializes minecraft blocks &
        // items
        REGISTER_BLOCK_FUNC(&Blocks::STONE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRASS_BLOCK,
                            material::Material({127, 178, 56, 255}));
        REGISTER_BLOCK_FUNC(&Blocks::DIRT, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::COBBLESTONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_PLANKS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_SAPLING,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BEDROCK, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FLOWING_WATER,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::WATER, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FLOWING_LAVA,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LAVA, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SAND, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRAVEL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GOLD_ORE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::IRON_ORE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::COAL_ORE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_LOG, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_LEAVES,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SPONGE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GLASS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::RED_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ORANGE_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::YELLOW_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CHARTREUSE_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIME_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SPRING_GREEN_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CYAN_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CAPRI_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIGHT_BLUE_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ULTRAMARINE_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PURPLE_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::VIOLET_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MAGENTA_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PINK_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRAY_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIGHT_GRAY_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::WHITE_WOOL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DANDELION,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::POPPY, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BROWN_MUSHROOM,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::RED_MUSHROOM,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GOLD_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::IRON_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DOUBLE_SMOOTH_STONE_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SMOOTH_STONE_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BRICKS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::TNT, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BOOKSHELF,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MOSSY_COBBLESTONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OBSIDIAN,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ROPE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SANDSTONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SNOW_LAYER,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FIRE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ICE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CERAMIC_TILE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MAGMA_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::QUARTZ_PILLAR,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CRATE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::STONE_BRICKS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::TORCH, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CHEST, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GEAR, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DIAMOND_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CRAFTING_TABLE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FARMLAND,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::WHEAT, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FURNACE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIT_FURNACE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_DOOR,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LADDER, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_SIGN,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::RAIL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MOB_SPAWNER,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::COBBLESTONE_STAIRS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_STAIRS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::IRON_DOOR,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LEVER, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::REDSTONE_DUST,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::REDSTONE_TORCH,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::STONE_BUTTON,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::STONE_PRESSURE_PLATE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_PRESSURE_PLATE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SNOW_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CACTUS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CLAY, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SUGAR_CANE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::JUKEBOX, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_FENCE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NETHERRACK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SOUL_SAND,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GLOWSTONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PUMPKIN, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GLOWING_PUMPKIN,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NETHER_PORTAL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BIRCH_LEAVES,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BIRCH_LOG,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CAKE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DISPENSER,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LAPIS_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NOTE_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CORAL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BED, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::REDSTONE_REPEATER,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PETRIFIED_OAK_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SANDSTONE_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SEAMLESS_STONE_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::APRIL_FOOLS_CHEST,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BIRCH_SAPLING,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::COBWEB, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DETECTOR_RAIL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::POWERED_RAIL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SPRUCE_SAPLING,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DEAD_BUSH,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRASS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FERN, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_TRAPDOOR,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PISTON, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::STICKY_PISTON,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PISTON_HEAD,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BRICK_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BRICK_STAIRS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::STONE_BRICK_SLAB,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::STONE_BRICK_STAIRS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CRACKED_STONE_BRICKS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MOSSY_STONE_BRICKS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::INFESTED_STONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::INFESTED_COBBLESTONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::INFESTED_STONE_BRICKS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GLASS_PANE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_FENCE_GATE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::IRON_BARS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MELON, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MELON_STEM,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PUMPKIN_STEM,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MUSHROOM_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MUSHROOM_STEM,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::RED_MUSHROOM_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BROWN_MUSHROOM_BLOCK,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::VINE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BREWING_STAND,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CAULDRON,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DRAGON_EGG,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ENCHANTMENT_TABLE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::END_PORTAL,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::END_PORTAL_FRAME,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::END_STONE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LILY_PAD,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MYCELIUM,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NETHER_BRICKS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NETHER_BRICK_FENCE,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NETHER_BRICK_STAIRS,
                            material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::NETHER_WART,
                            material::Material({0, 0, 0, 0}));
    }

    BlockRegistry &BlockRegistry::getInstance() {
        static BlockRegistry sInstance;
        return sInstance;
    }

    void BlockRegistry::registerBlock(
        const lodestone::common::registry::Identifier *id, const Block *block) {
        if (mBlocks.contains(id))
            throw std::runtime_error(
                std::format("Block '{}' is already registered", *id));

        item::ItemRegistry::getInstance().registerItem(id, block->getItem());
        mBlocks[id] = std::move(block);
#if CMAKE_BUILD_DEBUG
        std::cout << "Registered block '" << *id << "'" << std::endl;
#endif
    }

    bool BlockRegistry::registerBlockIfNonExistent(
        const lodestone::common::registry::Identifier *id,
        const Block *block) noexcept {
        if (mBlocks.contains(id))
            return false;

        item::ItemRegistry::getInstance().registerItemIfNonExistent(
            id, block->getItem());
        mBlocks[id] = std::move(block);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered block '" << *id << "'" << std::endl;
#endif

        return true;
    }

    const Block *BlockRegistry::getBlock(
        const lodestone::common::registry::Identifier *id) const {
        if (const auto it = mBlocks.find(id); it != mBlocks.end())
            return it->second;

        return nullptr;
    }

    const Block *BlockRegistry::operator[](
        const lodestone::common::registry::Identifier *id) const {
        return getBlock(id);
    }
} // namespace lodestone::level::block