use rayon::iter::ParallelIterator;
use std::collections::HashSet;
use std::fs;
use std::fs::{create_dir_all, remove_dir_all, File};
use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use flate2::read::{GzDecoder, ZlibDecoder};
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::Chunk;
use lodestone_level::level::chunk_section::BlockPaletteVec;
use lodestone_level::level::region::{ChunkLocation, Compression};
use lodestone_level::level::{metadata, Coords, Level};
use quartz_nbt::io::{write_nbt, Flavor};
use quartz_nbt::{io, NbtCompound, NbtList, NbtTag};
use rayon::iter::IntoParallelRefIterator;
use std::io::{BufWriter, Cursor, Read, Seek, SeekFrom, Write};
use std::path::Path;

// TODO LIST
// move world folder reading into separate thing, make directory readers only read the `regions` folder.

pub trait Anvil {
    /// Creates a Level from an anvil world's directory
    fn read_anvil_dir(path: &Path) -> Result<Level, String>;
    /// Reads Level.dat from an anvil world
    ///
    /// This method will soon be moved to its own thing as the impl should be separated from the format itself.
    fn read_anvil_level(level_name: String, data: Vec<u8>) -> Result<Level, String>;
    /// Reads an anvil region into an existing level
    fn read_anvil_region(&mut self, data: Vec<u8>);
    /// Writes an anvil world directory from a Level
    fn write_anvil_dir(&self, path: &Path);
    /// Writes an anvil world style level.dat file
    ///
    /// This method will soon be moved to its own thing as the impl should be separated from the format itself.
    fn write_anvil_level(&self, level_name: String) -> Vec<u8>;
    /// Writes a single Anvil region from given coords
    fn write_anvil_region(&self, coords: Coords) -> Vec<u8>;
}
pub trait AnvilChunk {
    /// Reads an anvil chunk
    fn read_anvil_chunk(data: Vec<u8>) -> Result<(Chunk, Coords), String>;
    /// Writes out an anvil chunk
    fn write_anvil_chunk(&self, coords: &Coords) -> Vec<u8>;
    // fn write_anvil(&self, out: &mut Vec<u8>, coords: Coords);
}

impl Anvil for Level {
    fn read_anvil_dir(path: &Path) -> Result<Level, String> {
        log::debug!("Reading level from {:?}", path);
        let level_dat = path.join("level.dat");

        if !level_dat.exists() && !level_dat.is_file() {
            return Err("level.dat does not exist or is not a file!".to_string());
        }

        let data = fs::read(level_dat).map_err(|e| e.to_string())?;
        let level_name = path
            .file_name()
            .unwrap()
            .to_str()
            .unwrap_or("New World")
            .to_string();
        let mut lvl = Self::read_anvil_level(level_name, data)
            .expect("Failed to parse anvil level from level.dat!");

        let region_dir = path.join("region");
        if !region_dir.exists() && !region_dir.is_dir() {
            return Err("Region directory does not exist or is not a directory!".to_string());
        }

        for entry in fs::read_dir(region_dir).map_err(|e| e.to_string())? {
            let p = entry.map_err(|e| e.to_string())?.path();
            if !p.is_file() || !p.extension().map_or(false, |ext| ext == "mca") {
                continue;
            }
            log::debug!("Reading region from {:?}", p);

            let data: Vec<u8> = fs::read(p).map_err(|e| e.to_string())?;
            Self::read_anvil_region(&mut lvl, data);
        }

        Ok(lvl)
    }

    #[allow(unused_variables)]
    fn read_anvil_level(level_name: String, data: Vec<u8>) -> Result<Level, String> {
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::GzCompressed)
            .expect("Anvil save NBT data")
            .0;

        let root: &NbtCompound = nbt.get(metadata::DATA).unwrap();

        let game_type: i32 = root.get(metadata::GAME_TYPE).expect("GameType value");
        let generator_name: &str = root
            .get(metadata::GENERATOR_NAME)
            .expect("GeneratorName value");
        let generator_version: i32 = root
            .get(metadata::GENERATOR_VERSION)
            .expect("GeneratorVersion value");
        let hard_core: bool = root.get(metadata::HARD_CORE).expect("Hardcore value");
        let last_played: i64 = root.get(metadata::LAST_PLAYED).expect("LastPlayed value");
        let level_name: &str = root.get(metadata::LEVEL_NAME).expect("LevelName value");
        let map_features: bool = root.get(metadata::MAP_FEATURES).expect("MapFeatures value");
        let raining: bool = root.get(metadata::RAINING).expect("Raining value");
        let rain_time: i32 = root.get(metadata::RAIN_TIME).expect("RainTime value");
        let random_seed: i64 = root.get(metadata::RANDOM_SEED).expect("RandomSeed value");
        let size_on_disk: i64 = root.get(metadata::SIZE_ON_DISK).expect("SizeOnDisk value");
        let spawn_x: i32 = root.get(metadata::SPAWN_X).expect("SpawnX value");
        let spawn_y: i32 = root.get(metadata::SPAWN_Y).expect("SpawnY value");
        let spawn_z: i32 = root.get(metadata::SPAWN_Z).expect("SpawnZ value");
        let thundering: bool = root.get(metadata::THUNDERING).expect("Thundering value");
        let thunder_time: i32 = root.get(metadata::THUNDER_TIME).expect("ThunderTime value");
        let time: i64 = root.get(metadata::TIME).expect("Time value");
        let version: i32 = root.get(metadata::VERSION).expect("Version value");

        let mut lvl = Level::new_with_name(level_name.to_string());
        lvl.time = time;
        lvl.custom_data
            .set_value::<i32>(metadata::GAME_TYPE.to_string(), game_type);
        lvl.custom_data.set_value::<String>(
            metadata::GENERATOR_NAME.to_string(),
            generator_name.to_string(),
        );
        lvl.custom_data
            .set_value::<i32>(metadata::GENERATOR_VERSION.to_string(), generator_version);
        lvl.custom_data
            .set_value::<bool>(metadata::HARD_CORE.to_string(), hard_core);
        lvl.custom_data
            .set_value::<i64>(metadata::LAST_PLAYED.to_string(), last_played);
        lvl.custom_data
            .set_value::<String>(metadata::LEVEL_NAME.to_string(), level_name.to_string());
        lvl.custom_data
            .set_value::<bool>(metadata::MAP_FEATURES.to_string(), map_features);
        lvl.custom_data
            .set_value::<bool>(metadata::RAINING.to_string(), raining);
        lvl.custom_data
            .set_value::<i32>(metadata::RAIN_TIME.to_string(), rain_time);
        lvl.custom_data
            .set_value::<i64>(metadata::RANDOM_SEED.to_string(), random_seed);
        lvl.custom_data
            .set_value::<i64>(metadata::SIZE_ON_DISK.to_string(), size_on_disk);
        lvl.custom_data
            .set_value::<bool>(metadata::THUNDERING.to_string(), thundering);
        lvl.custom_data
            .set_value::<i32>(metadata::THUNDER_TIME.to_string(), thunder_time);
        lvl.custom_data
            .set_value::<i64>(metadata::TIME.to_string(), time);
        lvl.custom_data
            .set_value::<i32>(metadata::VERSION.to_string(), version);

        Ok(lvl)
    }

    fn read_anvil_region(&mut self, data: Vec<u8>) {
        let mut c = Cursor::new(data);
        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];

        for l in locations.iter_mut() {
            let offset = c.read_u24::<BigEndian>().expect("Offset in location");
            let size = c.read_u8().expect("Size in location");

            *l = ChunkLocation { offset, size };
        }

        for ts in timestamps.iter_mut() {
            *ts = c.read_i32::<BigEndian>().expect("Chunk timestamp");
        }

        // TODO: find a way to make parallel
        let chunks: Vec<(Coords, Chunk)> = locations
            .par_iter()
            .filter_map(|l| {
                if l.size == 0 {
                    return None;
                }
                let mut c = c.clone();
                c.set_position((l.offset as u64) * 4096);

                let len = c.read_u32::<BigEndian>().expect("Chunk byte length");
                let comp = c.read_i8().expect("Chunk compression");
                let compression = Compression::try_from(comp).expect("Chunk compression enum");

                let mut compressed = vec![0u8; (len - 1) as usize];
                // wtf is this slice stuff
                c.read_exact(compressed.as_mut_slice())
                    .expect("Compressed chunk data");

                let mut chunk_data: Vec<u8> = Vec::new();

                // TODO: support the other 2 methods
                let dec: Option<Box<dyn Read>> = match compression {
                    Compression::Zlib => {
                        Some(Box::new(ZlibDecoder::new(Cursor::new(compressed.clone()))))
                    } // cloning seems really janky...?
                    Compression::GZip => {
                        Some(Box::new(GzDecoder::new(Cursor::new(compressed.clone()))))
                    }
                    Compression::None => None,
                    _ => {
                        panic!("Unsupported compression format!")
                    } // is this a good idea? I don't know if you can "catch" a panic...
                };

                if compression != Compression::None {
                    dec.expect("Decompressor")
                        .read_to_end(&mut chunk_data)
                        .expect("Decompressed chunk data");
                } else {
                    chunk_data = compressed.to_vec();
                }

                let ch = Chunk::read_anvil_chunk(chunk_data).expect("Region Chunk from data");
                Some((ch.1, ch.0))
            })
            .collect();

        for (coords, chunk) in chunks {
            self.add_chunk(coords, chunk);
        }
    }

    fn write_anvil_dir(&self, path: &Path) {
        if path.exists() && path.is_dir() {
            remove_dir_all(path).expect("Could not remove output folder!");
        }

        if !path.exists() && !path.is_file() {
            create_dir_all(path).expect("Could not create output folder!");
        }

        let level_dat = &path.join("level.dat");
        let region_dir = &path.join("region");
        let data_dir = &path.join("data");

        let level_name = path
            .file_name()
            .unwrap()
            .to_str()
            .unwrap_or("New World")
            .to_string();

        let level_dat_file = if !level_dat.exists() || level_dat.is_dir() {
            File::create(level_dat).expect("Could not create level.dat for Anvil level!")
        } else {
            File::open(level_dat).expect("Could not open level.dat")
        };

        // Write the level.dat
        let mut writer = BufWriter::new(level_dat_file);
        writer
            .write_all(&Self::write_anvil_level(self, level_name))
            .expect("Could not write to level.dat!");

        if !region_dir.exists() && !region_dir.is_file() {
            create_dir_all(region_dir).expect("Could not create region folder for Anvil level!");
        }

        if !data_dir.exists() && !data_dir.is_file() {
            create_dir_all(data_dir).expect("Could not create data folder for Anvil level!");
        }

        let mut region_coords = HashSet::new();
        for coords in self.get_chunks().keys() {
            let region_x = coords.x.div_floor(32);
            let region_z = coords.z.div_floor(32);
            region_coords.insert(Coords {
                x: region_x,
                z: region_z,
            });
        }

        region_coords.par_iter().for_each(|c| {
            let region_path = region_dir.join(format!("r.{}.{}.mca", c.x, c.z));
            let region_file = if !region_path.exists() || region_path.is_dir() {
                File::create(region_path).expect(
                    &*format!(
                        "Could not create region at {}, {} for Anvil level!",
                        c.x, c.z
                    )
                    .to_string(),
                )
            } else {
                File::open(region_path).expect(
                    &*format!("Could not open region at {}, {} for Anvil level!", c.x, c.z)
                        .to_string(),
                )
            };

            let region_data = self.write_anvil_region(c.clone());

            // Write the region data
            let mut writer = BufWriter::new(region_file);
            writer
                .write_all(&region_data)
                .expect("Could not write region!"); //.expect(
            // &*format!("Could not write to region at {}, {} for Anvil level!", c.x, &c.z).to_string(),
            //);
        });
    }

    fn write_anvil_level(&self, level_name: String) -> Vec<u8> {
        let mut level_nbt = NbtCompound::new();
        let mut level_data = NbtCompound::new();

        // TODO: Player tag
        let game_type = self
            .custom_data
            .get_value::<i32, &str>(metadata::GAME_TYPE)
            .unwrap_or(0);
        level_data.insert(metadata::GAME_TYPE, game_type);

        let generator_name = self
            .custom_data
            .get_value::<String, &str>(metadata::GENERATOR_NAME)
            .unwrap_or("default".to_string());
        level_data.insert(metadata::GENERATOR_NAME, generator_name);

        let generator_version = self
            .custom_data
            .get_value::<i32, &str>(metadata::GENERATOR_VERSION)
            .unwrap_or(1);
        level_data.insert(metadata::GENERATOR_VERSION, generator_version);

        let hard_core = self
            .custom_data
            .get_value::<bool, &str>(metadata::HARD_CORE)
            .unwrap_or(false);
        level_data.insert(metadata::HARD_CORE, hard_core);

        let last_played = self
            .custom_data
            .get_value::<i64, &str>(metadata::LAST_PLAYED)
            .unwrap_or(0);
        level_data.insert(metadata::LAST_PLAYED, last_played);

        let level_name = self
            .custom_data
            .get_value::<String, &str>(metadata::LEVEL_NAME)
            .unwrap_or(level_name);
        level_data.insert(metadata::LEVEL_NAME, level_name);

        let map_features = self
            .custom_data
            .get_value::<bool, &str>(metadata::MAP_FEATURES)
            .unwrap_or(false);
        level_data.insert(metadata::MAP_FEATURES, map_features);

        let raining = self
            .custom_data
            .get_value::<bool, &str>(metadata::RAINING)
            .unwrap_or(false);
        level_data.insert(metadata::RAINING, raining);

        let rain_time = self
            .custom_data
            .get_value::<i32, &str>(metadata::RAIN_TIME)
            .unwrap_or(0);
        level_data.insert(metadata::RAIN_TIME, rain_time);

        let random_seed = self
            .custom_data
            .get_value::<i64, &str>(metadata::RANDOM_SEED)
            .unwrap_or(0);
        level_data.insert(metadata::RANDOM_SEED, random_seed);

        // This will actually always be 0 for Anvil worlds...
        let size_on_disk = self
            .custom_data
            .get_value::<i64, &str>(metadata::SIZE_ON_DISK)
            .unwrap_or(0);
        level_data.insert(metadata::SIZE_ON_DISK, size_on_disk);

        // Write spawn tags
        level_data.insert(metadata::SPAWN_X, self.spawn.x);
        level_data.insert(metadata::SPAWN_Y, self.spawn.y);
        level_data.insert(metadata::SPAWN_Z, self.spawn.z);

        let thundering = self
            .custom_data
            .get_value::<bool, &str>(metadata::THUNDERING)
            .unwrap_or(false);
        level_data.insert(metadata::THUNDERING, thundering);

        let thunder_time = self
            .custom_data
            .get_value::<i32, &str>(metadata::THUNDER_TIME)
            .unwrap_or(0);
        level_data.insert(metadata::THUNDER_TIME, thunder_time);

        level_data.insert(metadata::TIME, self.time);

        // First Anvil version is labelled 19133
        let version = self
            .custom_data
            .get_value::<i32, &str>(metadata::VERSION)
            .unwrap_or(19133);
        level_data.insert(metadata::VERSION, version);

        level_nbt.insert("Data", level_data);

        let mut data: Vec<u8> = Vec::new();

        write_nbt(&mut data, Some("Data"), &level_nbt, Flavor::GzCompressed)
            .expect("Failed to write NBT data to level.dat");

        data
    }

    fn write_anvil_region(&self, coords: Coords) -> Vec<u8> {
        let out: Vec<u8> = Vec::new();
        let mut c = Cursor::new(out);

        let mut locations = vec![ChunkLocation::default(); 1024];
        let mut timestamps = vec![0i32; 1024];

        c.seek(SeekFrom::Start(0x2000)).expect("Chunk position");

        let min_chunk_x = coords.x * 32;
        let max_chunk_x = (coords.x + 1) * 32;

        let min_chunk_z = coords.z * 32;
        let max_chunk_z = (coords.z + 1) * 32;

        for chunk_z in min_chunk_z..max_chunk_z {
            for chunk_x in min_chunk_x..max_chunk_x {
                log::debug!(
                    "Writing chunk X: {}, Z: {} to region X: {}, Z: {}",
                    chunk_x,
                    chunk_z,
                    coords.x,
                    coords.z
                );
                let chunk_coords = &Coords {
                    x: chunk_x,
                    z: chunk_z,
                };
                let chunk = self.get_chunk(chunk_coords);
                match chunk {
                    Some(chunk) => {
                        let mut chunk_data = chunk.write_anvil_chunk(&chunk_coords);

                        let len = chunk_data.len();
                        let sector_size = ((len + 5) + 4095) / 4096;

                        let size = sector_size;
                        let offset = c.stream_position().unwrap() / 4096;

                        let idx = (chunk_x as usize % 32) + (chunk_z as usize % 32) * 32;
                        if idx > 1023 {
                            println!(
                                "WARN: Chunk at X: {}, Z: {} is out of bounds in the location table.",
                                chunk_x, chunk_z
                            );
                            continue;
                        }

                        locations[idx] = ChunkLocation {
                            offset: offset as u32,
                            size: size as u8,
                        };
                        timestamps[idx] = 0;

                        c.write_i32::<BigEndian>(len as i32).expect("Chunk size");
                        c.write_i8(2).expect("Chunk compression type");
                        c.write_all(chunk_data.as_mut_slice()).expect("Chunk data");

                        let p = sector_size * 4096 - (len + 5);
                        if p > 0 {
                            c.write_all(&vec![0u8; p]).unwrap();
                        }
                    }
                    None => {}
                }
            }
        }

        c.seek(SeekFrom::Start(0)).unwrap();

        for l in locations.iter() {
            c.write_u24::<BigEndian>(l.offset).expect("Offset");
            c.write_u8(l.size).expect("Size");
        }

        c.seek(SeekFrom::Start(0x1000)).unwrap();

        for t in timestamps.iter() {
            c.write_i32::<BigEndian>(*t).expect("Timestamp");
        }

        c.into_inner()
    }
}

impl AnvilChunk for Chunk {
    fn read_anvil_chunk(data: Vec<u8>) -> Result<(Chunk, Coords), String> {
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::Uncompressed)
            .expect("Chunk NBT data")
            .0;

        let version: i32 = nbt.get(metadata::DATA_VERSION).unwrap_or(0);

        // I created 24 instances to find the correct version (17w47a)
        // and then on the wiki talk page, someone already mentioned it, back in 2017...
        // Why didn't the search page show me the message???
        if version >= 1451 {
            panic!("Section palettes (introduced in 17w47a) are not yet supported.");
        }

        // TODO: we do not handle extended block IDs yet.

        let level: &NbtCompound = nbt.get("Level").expect("Level compound tag");

        let x: i32 = level.get("xPos").expect("Chunk x position");
        let z: i32 = level.get("zPos").expect("Chunk z position");
        let last_update: i64 = level.get("LastUpdate").expect("Chunk last modified");
        let inhabited_time: i64 = level.get("InhabitedTime").unwrap_or(0);
        // let entities: &NbtList = level.get("Entities").expect("Chunk entities");
        // let tile_entities: &NbtList = level.get("TileEntities").expect("Chunk tile entities");
        let has_populated: i8 = level.get("TerrainPopulated").expect("Chunk has populated"); // DOES NOT EXIST ON 1.16 (TODO: DataVersion check to see what is available)
        let has_light_populated: i8 = level.get("LightPopulated").unwrap_or(1);

        let mut c = Chunk::new(256);

        c.custom_data
            .set_value(metadata::DATA_VERSION.to_string(), version);
        c.custom_data
            .set_value(metadata::LAST_UPDATE.to_string(), last_update);
        c.custom_data
            .set_value(metadata::INHABITED_TIME.to_string(), inhabited_time);
        c.custom_data
            .set_value(metadata::TERRAIN_POPULATED.to_string(), has_populated);
        c.custom_data
            .set_value(metadata::LIGHT_POPULATED.to_string(), has_light_populated);

        // love sections
        let sections: &NbtList = level.get(metadata::SECTIONS).expect("Chunk sections");

        sections.iter().for_each(|s| {
            if let NbtTag::Compound(section) = s {
                let sy: i8 = section.get("Y").expect("Section Y");
                let blocks: &[u8] = section.get("Blocks").expect("Section blocks");

                let sc = c.get_or_create_chunk_section_mut(sy as i16 * 16);
                let mut p = BlockPaletteVec::new();

                // MAY BE WEIRD/SLOW, UNSURE.
                let new: Vec<u16> = blocks.par_iter().map(|v| *v as u16).collect();

                for value in &new {
                    p.push_ref(value);
                }

                sc.blocks = p;
            }
        });

        Ok((c, Coords { x, z }))
    }

    fn write_anvil_chunk(&self, coords: &Coords) -> Vec<u8> {
        let mut chunk_data: Vec<u8> = Vec::new();

        let mut chunk_nbt = NbtCompound::new();
        let mut chunk_level = NbtCompound::new();

        let data_version = self
            .custom_data
            .get_value::<i32, &str>(metadata::DATA_VERSION)
            .unwrap_or(0);
        chunk_level.insert(metadata::DATA_VERSION, data_version);

        chunk_level.insert(metadata::POS_X, coords.x);
        chunk_level.insert(metadata::POS_Z, coords.z);

        let last_update = self
            .custom_data
            .get_value::<i64, &str>(metadata::LAST_UPDATE)
            .unwrap_or(0);
        chunk_level.insert(metadata::LAST_UPDATE, last_update);

        let inhabited_time = self
            .custom_data
            .get_value::<i64, &str>(metadata::INHABITED_TIME)
            .unwrap_or(0);
        chunk_level.insert(metadata::INHABITED_TIME, inhabited_time);

        // TODO: Implement entities properly
        let _entities = chunk_level.insert(metadata::ENTITIES.to_string(), NbtList::new());
        let _tile_entities =
            chunk_level.insert(metadata::TILE_ENTITIES.to_string(), NbtList::new());

        let has_populated = self
            .custom_data
            .get_value::<i8, &str>(metadata::TERRAIN_POPULATED)
            .unwrap_or(1);
        chunk_level.insert(metadata::TERRAIN_POPULATED, has_populated);

        // TODO: calculate light ourselves
        // turning this option to 0 tells the game that lighting has not yet been calculated, which gives us a free pass when dealing with Anvil, but also makes the world load take forever.
        let light_populated = self
            .custom_data
            .get_value::<i8, &str>(metadata::LIGHT_POPULATED)
            .unwrap_or(1);
        chunk_level.insert(metadata::LIGHT_POPULATED, light_populated);

        chunk_level.insert(
            metadata::HEIGHT_MAP,
            self.get_heightmap()
                .iter()
                .map(|v| *v as i32)
                .collect::<Vec<i32>>(),
        );

        // Write chunk sections
        let mut sections: NbtList = NbtList::new();

        for i in 0..self.chunk_sections.len() {
            let chunk_section = &self.chunk_sections[i];
            let mut chunk_section_tag = NbtCompound::new();

            chunk_section_tag.insert("Y", i as i8);
            chunk_section_tag.insert(
                "Blocks",
                chunk_section
                    .blocks
                    .iter()
                    .map(|v| *v as u8)
                    .collect::<Vec<u8>>(),
            );
            chunk_section_tag.insert(metadata::DATA, vec![0u8; 2048]);
            chunk_section_tag.insert(metadata::BLOCK_LIGHT, vec![0xFFu8; 2048]);
            chunk_section_tag.insert(metadata::SKY_LIGHT, vec![0xFFu8; 2048]);

            sections.push(chunk_section_tag);
        }

        chunk_level.insert(metadata::SECTIONS, sections);

        chunk_nbt.insert(metadata::LEVEL, chunk_level);

        write_nbt(
            &mut chunk_data,
            Some(metadata::LEVEL),
            &chunk_nbt,
            Flavor::ZlibCompressed,
        )
        .expect("Chunk data could not be serialized!");

        chunk_data
    }
}
