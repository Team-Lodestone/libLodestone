# libLodestone
Provides file type reading, file type writing, and world & format conversion for most editions and versions of Minecraft.

LCE formats will be handled by [libLCE](https://github.com/DexrnZacAttack/libLCE).

### Libraries
| Name                                 | Description                                  |
|--------------------------------------|----------------------------------------------|
| [Lodestone.Level](/projects/Level)   | Voxel world engine with dynamic registration |
| [Lodestone.Java](/projects/Java)     | Java Edition format converters               |
| [Lodestone.Common](/projects/Common) | Common dependencies for all projects         |
| [Lodestone.Tests](/projects/Tests)   | Tests for our converters                     |


# Roadmap
### Goals
- [X] World Engine
    - [X] Chunked Level
      - [X] Chunk Sections
      - [ ] Palettes (for memory usage)
      - [ ] Lighting calculation (maybe?)
    - [ ] Dynamic Block & Material registration
      - `DynamicBlock`
      - `DynamicMaterial`
    - [X] Internal Block IDs
        - [X] Block ID conversion map between versions
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
    - [ ] Infdev (Alpha Save Format)
    - [ ] Alpha (Alpha Save Format)
    - [ ] MCR
    - [ ] Anvil
    - [ ] 1.13+ Anvil
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