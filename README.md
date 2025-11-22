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
| Name                                                  | Description                       |
|-------------------------------------------------------|-----------------------------------|
| [Lodestone.Java](/projects/Converters/Minecraft/Java) | Minecraft: Java Edition Converter |


# Roadmap
### Goals
- [X] World Engine
    - [X] Chunked Level
      - [X] Chunk Sections
      - [ ] Palettes (for memory usage)
    - [ ] Lighting calculation (maybe?)
    - [ ] Biomes
    - [ ] POI/Structure system
    - [X] Players (store player data per world)
    - [ ] Dynamic registration
      - [ ] `DynamicBlock`
      - [ ] `DynamicMaterial`
      - [ ] `DynamicBiome`
    - [X] Internal Block IDs
        - [X] Block ID conversion map between versions
          - [X] Dynamic block map
          - [X] Versioned block map
        - [ ] Item ID conversion map between versions
          - [ ] Dynamic item map
          - [ ] Versioned item map
        - [ ] Properly convert block states and other data
    - [ ] Entities
        - [ ] Tile Entities
    - [ ] Block Material Map (for the world map image generation)
### Formats
- [ ] Java
    - [ ] Classic
        - [X] .Mine V1
        - [X] .Mine V2
        - [ ] .Mine V3
        - [ ] ClassicWorld (CW)
        - [ ] [MCGalaxy](https://github.com/ClassiCube/MCGalaxy) Level (LVL)
    - [ ] Indev (MCLevel)
    - [ ] Infdev 20100624 (Zone File Format)
    - [ ] Infdev/Alpha (Alpha Save Format)
    - [X] McRegion
    - [ ] Anvil
    - [ ] 1.13+ Anvil
    - [ ] 1.18+ Anvil
- [ ] LCE
    - [ ] V11
    - [ ] V12
    - [ ] V13
- [ ] 3DS
- [ ] PE/Bedrock

# Credits
- [BinaryIO](https://github.com/DexrnZacAttack/libBIO)
- [libNBT++ 2](https://github.com/PrismLauncher/libnbtplusplus)

# Disclaimer
This project is not an official Microsoft, Minecraft, nor Mojang Studios product.