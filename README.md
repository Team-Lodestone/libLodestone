# libLodestone
Provides reading, writing, and format conversion for most editions and versions of Minecraft.

~~See it in action with our finite world reader example found [here](https://team-lodestone.github.io/examples/finite.html).~~
Not yet available

LCE formats will be handled by [libLCE](https://github.com/DexrnZacAttack/libLCE), once bindings are made for it.

## Roadmap
### Formats
  - [ ] Java 
    - [ ] Classic 
      - [X] .Mine V1
      - [X] .Mine V2
      - [ ] .Mine V3
      - [X] ClassicWorld (CW)
      - [X] [MCGalaxy](https://github.com/ClassiCube/MCGalaxy) Level (LVL)
    - [X] Indev (MCLevel)
    - [X] Infdev (Alpha Save Format)
    - [X] Alpha (Alpha Save Format)
    - [X] MCR
    - [X] Anvil
    - [ ] 1.13 Anvil 
  - [ ] LCE
    - [ ] V11
    - [ ] V12
    - [ ] V13
  - [ ] 3DS
  - [ ] PE (not known at this time)
### Goals
  - [X] Internal Format
    - [X] Chunked
    - [X] Sections
    - [ ] Palettes (for memory usage)
  - [ ] Internal Block IDs
    - [ ] Block ID conversion map between versions
    - [ ] Properly convert block states and other data
  - [ ] Tile Entities
    - [ ] Entities 

# Disclaimer
This project is not an official Microsoft, Minecraft, nor Mojang Studios product.