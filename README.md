# libLodestone
Provides file type reading, file type writing, and world & format conversion for most editions and versions of Minecraft.

LCE formats will be handled by [libLCE](https://github.com/DexrnZacAttack/libLCE).

### Libraries
| Name                                                   | Description                                  |
|--------------------------------------------------------|----------------------------------------------|
| [Lodestone.Level](/projects/Libraries/Level)           | Voxel world engine with dynamic registration |
| [Lodestone.Conversion](/projects/Libraries/Conversion) | Conversion base classes & registries         |
| [Lodestone.Core](/projects/Libraries/Core)             | Core library, handles converter registration |
| [Lodestone.Common](/projects/Libraries/Common)         | Common dependencies for all projects         |
### Converters
| Name                                                                  | Description                                   |
|-----------------------------------------------------------------------|-----------------------------------------------|
| [Lodestone.Minecraft.Java](/projects/Converters/Minecraft/Java)       | Minecraft: Java Edition Converter             |
| [Lodestone.Minecraft.Console](/projects/Converters/Minecraft/Console) | Minecraft: Legacy Console Edition Converter   |
| [Lodestone.Minecraft.NN3DS](/projects/Converters/Minecraft/NN3DS)     | Minecraft: New Nintendo 3DS Edition Converter |
| [Lodestone.Minecraft.Web](/projects/Converters/Minecraft/Web)         | `classic.minecraft.net` World Converter       |


# Roadmap
<!-- Would you like to insert '→'?  -->
Bold → Required for 1.0.0 final release, all releases from there will follow major.minor.patch

## Goals
- [X] World Engine
    - [X] **Chunked Level**
      - [X] **Chunk Sections**
      - [X] **Palettes (for memory usage)**
    - [ ] Lighting calculation (maybe?)
    - [ ] **Biomes**
    - [ ] POI/Structure system
    - [X] **Players (store player data per world)**
    - [ ] Dynamic registration
      - [ ] `DynamicBlock`
      - [ ] `DynamicMaterial`
      - [ ] `DynamicBiome`
    - [ ] **Block definitions and properties**
    - [X] **Internal Block IDs**
        - [X] **Block ID conversion map between versions**
          - [X] Dynamic block map
          - [X] Versioned block map
        - [ ] **Item ID conversion map between versions**
          - [ ] Dynamic item map
          - [ ] Versioned item map
    - [ ] Entities
        - [ ] Tile Entities
    - [ ] Block Material Map (for the world map image generation)
## Formats
- [ ] [Java](https://github.com/Team-Lodestone/libLodestone/tree/main/projects/Converters/Minecraft/Java/README.md)
- [ ] LCE
    - [ ] V11
    - [ ] V12
    - [ ] V13
- [ ] 3DS
- [ ] PE/Bedrock

# Credits
- [BinaryIO](https://codeberg.org/Dexrn/libBIO)
- [libNBT++ 2](https://github.com/PrismLauncher/libnbtplusplus)
- [danilwhale](https://codeberg.org/danilwhale)

# Disclaimer
This project is not an official Microsoft, Minecraft, nor Mojang Studios product.
