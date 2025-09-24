# libLodestone
Provides reading, writing, and format conversion for most editions and versions of Minecraft.

~~See it in action with our finite world reader example found [here](https://team-lodestone.github.io/examples/finite.html).~~
Not yet available

LCE formats will be handled by [libLCE](https://github.com/DexrnZacAttack/libLCE), once bindings are made for it.

TODO: make writing also convert blocks instead of directly writing out internal block ids

## Roadmap
### Goals
- [X] Internal Format
    - [X] Chunked
    - [X] Sections
    - [X] [Palettes](https://github.com/alexdesander/palettevec) (for memory usage)
- [X] Internal Block IDs
    - [X] Block ID conversion map between versions
    - [ ] Properly convert block states and other data
- [ ] Entities 
    - [ ] Tile Entities
- [X] Block Material Map (for the world map image generation) 
- [ ] Code Cleanup
    - [ ] Figure out a better way to do block conversion
    - [ ] Refactor a bunch of things to be more consistent
- [ ] Performance Optimizations
- [ ] Merge into the Main branch (1.0.0)
### Formats
  - [ ] Java 
    - [ ] Classic 
      - [X] .Mine V1
      - [X] .Mine V2
      - [ ] .Mine V3
      - [X] ClassicWorld (CW)
      - [X] [MCGalaxy](https://github.com/ClassiCube/MCGalaxy) Level (LVL)
    - [X] Indev (MCLevel)
    - [ ] Infdev 20100624
       - Only reading works, writing is not yet complete. 
    - [X] Infdev (Alpha Save Format)
    - [X] Alpha (Alpha Save Format)
    - [X] MCR
    - [X] Anvil
    - [ ] 1.13+ Anvil 
  - [ ] LCE
    - [ ] V11
    - [ ] V12
    - [ ] V13
  - [ ] 3DS
  - [ ] PE (not known at this time)
# Disclaimer
This project is not an official Microsoft, Minecraft, nor Mojang Studios product.