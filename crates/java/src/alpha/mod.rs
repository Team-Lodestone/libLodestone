pub mod inf_624;

use flate2::read::GzDecoder;
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_common::types::hashmap_ext::Value::{Bool, Int64};
use lodestone_common::types::vec3i::Vec3i;
use lodestone_common::util::{base36, McVersion};
use lodestone_level::block::conversion::get_internal_block_id;
use lodestone_level::block::{BlockInfo};
use lodestone_level::entity::block_entity::BlockEntity;
use lodestone_level::level::chunk::{Chunk, CHUNK_LENGTH};
use lodestone_level::level::{metadata, Coords, Level};
use quartz_nbt::io::{write_nbt, Flavor};
use quartz_nbt::{io, NbtCompound, NbtList, NbtTag};
use std::fs;
use std::fs::File;
use std::io::{BufWriter, Cursor, Write};
use std::path::Path;
use std::time::{Duration, SystemTime, UNIX_EPOCH};

pub trait AlphaLevel {
    fn new(name: String) -> Level;

    fn read_alpha_dir(version: McVersion, path: &Path) -> Result<Level, String>;

    fn write_alpha_dir(&mut self, version: McVersion, path: &Path);

    fn read_alpha_level(
        version: McVersion,
        level_name: String,
        data: Vec<u8>,
    ) -> Result<Level, String>;

    fn write_alpha_level(&self, version: McVersion) -> Vec<u8>;
}

pub trait AlphaChunk {
    fn read_alpha_chunk(version: McVersion, data: Vec<u8>) -> Result<(Coords, Chunk), String>;
    fn read_alpha_chunk_into_existing(lvl: &mut Level, version: McVersion, data: Vec<u8>);
    fn write_alpha_chunk(&mut self, version: McVersion, coords: &Coords) -> Vec<u8>;
}

impl AlphaChunk for Chunk {
    #[allow(unused_variables)]
    fn read_alpha_chunk(version: McVersion, data: Vec<u8>) -> Result<(Coords, Chunk), String> {
        let chunk_nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::GzCompressed)
            .expect("Alpha chunk NBT data")
            .0;

        let root: &NbtCompound = chunk_nbt.get("Level").unwrap();

        let last_update: i64 = root.get("LastUpdate").expect("LastUpdate value");
        let terrain_populated: bool = root
            .get("TerrainPopulated")
            .expect("TerrainPopulated value");
        let chunk_x: i32 = root.get("xPos").expect("xPos value");
        let chunk_z: i32 = root.get("zPos").expect("zPos value");
        let block_light: &Vec<i8> = root.get("BlockLight").expect("BlockLight array");
        let blocks: &Vec<i8> = root.get("Blocks").expect("Blocks array");
        let data: &Vec<i8> = root.get("Data").expect("Data array");
        // let height_map: &Vec<i8> = root.get("HeightMap").expect("Heightmap");
        let sky_light: &Vec<i8> = root.get("SkyLight").expect("SkyLight array");
        let tile_entities = root
            .get::<str, &NbtList>("TileEntities")
            .expect("TileEntities list");

        // Store chunk data into chunk
        let coords: Coords = Coords {
            x: chunk_x,
            z: chunk_z,
        };
        let mut chunk = Chunk::new(128);
        chunk
            .custom_data
            .set_value(metadata::LAST_UPDATE.to_string(), Int64(last_update));
        chunk.custom_data.set_value(
            metadata::TERRAIN_POPULATED.to_string(),
            Bool(terrain_populated),
        );

        // TODO: Batch this
        // TODO: Set state and lighting
        let chunk_length = CHUNK_LENGTH as usize;
        let chunk_height = chunk.height as usize;
        for y in 0..chunk_height {
            let chunk_y = y as i16;

            for x in 0..16 {
                for z in 0..16 {
                    let idx = y + (z * chunk_height + (x * chunk_height * chunk_length));

                    let blk = blocks[idx];
                    if blk != 0 {
                        let blk = get_internal_block_id(version, &BlockInfo { id: Some(blk as u32), variant: None, str: None });

                        match blk {
                            Some(blk) => {
                                chunk.set_block(x as i8, chunk_y, z as i8, blk);
                            }
                            None => {}
                        }
                    }

                    // chunk.set_state(x, y, z, data[i] as u8);
                    // chunk.set_light(SKY, x, y, z, sky_light[i] as u8);
                    // chunk.set_light(BLOCK, x, y, z, block_light[i] as u8);
                }
            }
        }

        for tile_entity in tile_entities.iter() {
            let compound = match tile_entity {
                NbtTag::Compound(tile_entity) => Ok(tile_entity),
                _ => Err("Not a compound"),
            };

            if compound.is_ok() {
                let tile_entity = BlockEntity::from_nbt(McVersion::Alpha1_2_6, compound?);

                if tile_entity.is_some() {
                    let tile_entity = tile_entity.expect("Failed to unwrap tile entity!");
                    let pos = Vec3i {
                        x: tile_entity.x,
                        y: tile_entity.y,
                        z: tile_entity.z,
                    };
                    chunk.add_block_entity(pos, tile_entity);
                }
            }
        }

        Ok((coords, chunk))
    }

    fn read_alpha_chunk_into_existing(lvl: &mut Level, version: McVersion, data: Vec<u8>) {
        let chunk: (Coords, Chunk) = Self::read_alpha_chunk(version, data)
            .expect("Could not read alpha chunk into existing level!");

        lvl.add_chunk(chunk.0, chunk.1);
    }

    #[allow(unused_variables)]
    fn write_alpha_chunk(&mut self, version: McVersion, coords: &Coords) -> Vec<u8> {
        let mut chunk_data: Vec<u8> = Vec::new();

        self.set_height(128);

        let mut chunk_nbt = NbtCompound::new();
        let mut chunk_level = NbtCompound::new();

        // TODO: Implement entities properly
        let _entities = chunk_level.insert(metadata::ENTITIES.to_string(), NbtList::new());
        let mut tile_entities = NbtList::new();
        for (coords, tile_entity) in self.block_entities.iter() {
            let nbt = tile_entity.to_nbt(McVersion::Alpha1_2_6);

            if nbt.is_some() {
                tile_entities.push(nbt.unwrap());
            }
        }
        let tile_entities = chunk_level.insert(metadata::TILE_ENTITIES.to_string(), tile_entities);

        let last_update = chunk_level.insert(
            metadata::LAST_UPDATE.to_string(),
            self.custom_data
                .get_value::<i64, &str>(metadata::LAST_UPDATE)
                .unwrap_or(0),
        );

        let terrain_populated = chunk_level.insert(
            metadata::TERRAIN_POPULATED.to_string(),
            self.custom_data
                .get_value::<bool, &str>(metadata::TERRAIN_POPULATED)
                .unwrap_or(true),
        );

        let chunk_x = chunk_level.insert("xPos", coords.x);
        let chunk_z = chunk_level.insert("zPos", coords.z);

        let block_light = chunk_level.insert(metadata::BLOCK_LIGHT, vec![15i8; 16384]);

        // TODO: This is jank. Please fix.
        let blocks = chunk_level.insert::<_, Vec<u8>>(
            metadata::BLOCKS.to_string(),
            self.get_all_blocks_converted(version).iter().map(|x| x.id.unwrap_or(0) as u8).collect(),
        );

        let data = chunk_level.insert::<_, Vec<u8>>(metadata::DATA.to_string(), vec![0u8; 16384]);
        let height_map = chunk_level.insert::<_, Vec<u8>>(
            metadata::HEIGHT_MAP.to_string(),
            self.get_heightmap().iter().map(|&x| x as u8).collect(),
        );
        let sky_light = chunk_level.insert(metadata::SKY_LIGHT.to_string(), vec![15i8; 16384]);

        chunk_nbt.insert(metadata::LEVEL, chunk_level);

        write_nbt(
            &mut chunk_data,
            Some(metadata::LEVEL),
            &chunk_nbt,
            Flavor::GzCompressed,
        )
        .expect("Chunk data could not be serialized!");

        chunk_data
    }
}

impl AlphaLevel for Level {
    fn new(name: String) -> Level {
        Level::new_with_name(name)
    }

    fn read_alpha_dir(version: McVersion, path: &Path) -> Result<Level, String> {
        log::debug!("Reading level.dat");
        let level_dat = path.join("level.dat");

        if !level_dat.exists() && !level_dat.is_file() {
            return Err("level.dat does not exist or is not a file!".to_string());
        }

        let data = fs::read(level_dat).map_err(|e| e.to_string())?;
        let level_name = path
            .file_name()
            .unwrap()
            .to_str()
            .unwrap_or("World0")
            .to_string();
        let mut lvl =
            Self::read_alpha_level(version, level_name, data).expect("Could not parse level!");

        for chunk_x_entry in fs::read_dir(path).map_err(|e| e.to_string())? {
            let chunk_x = &chunk_x_entry.unwrap().path();
            if !chunk_x.is_dir() {
                continue;
            }
            for chunk_z_entry in fs::read_dir(&chunk_x).map_err(|e| e.to_string())? {
                let chunk_z = &chunk_z_entry.unwrap().path();
                if !chunk_z.is_dir() {
                    continue;
                }
                let chunk_dir = path
                    .join(chunk_x.file_name().unwrap())
                    .join(chunk_z.file_name().unwrap());
                if !chunk_dir.exists() {
                    println!("{:?}", chunk_dir);
                    continue;
                }
                for entry in fs::read_dir(chunk_dir).map_err(|e| e.to_string())? {
                    let p = entry.map_err(|e| e.to_string())?.path();
                    if !p.is_file() || !p.extension().map_or(false, |ext| ext == "dat") {
                        continue;
                    }
                    println!("Reading {:?}", p);

                    let data: Vec<u8> = fs::read(p).expect("Read file");

                    Chunk::read_alpha_chunk_into_existing(&mut lvl, version, data);
                }
            }
        }
        println!(
            "World bounds: {} {} {}",
            lvl.get_block_width(),
            lvl.get_block_height(),
            lvl.get_block_length()
        );
        Ok(lvl)
    }

    fn write_alpha_dir(&mut self, version: McVersion, path: &Path) {
        let level_dat = path.join("level.dat");

        let level_data = self.write_alpha_level(version);
        let level_dat_file = File::create(level_dat).unwrap();
        let mut writer = BufWriter::new(level_dat_file);
        writer
            .write_all(&level_data)
            .expect("Could not write to level.dat!");
        writer.flush().expect("Could not flush level.dat!");

        for (coords, chunk) in self.get_chunks_mut() {
            let chunk_data = chunk.write_alpha_chunk(version, &coords);

            let chunk_dir = path
                .join(base36(coords.x & 63) + "/")
                .join(base36(coords.z & 63) + "/");
            if !chunk_dir.exists() {
                fs::create_dir_all(&chunk_dir).expect("Chunk directory could not be created!");
            }

            let chunk_file =
                chunk_dir.join(format!("c.{}.{}.dat", base36(coords.x), base36(coords.z)));

            if !chunk_file.exists() {
                File::create(&chunk_file).expect("Chunk file could not be created!");
            }

            fs::write(chunk_file, &chunk_data).expect("Chunk file could not be written!");
        }
    }

    fn read_alpha_level(
        version: McVersion,
        level_name: String,
        data: Vec<u8>,
    ) -> Result<Level, String> {
        let nbt = io::read_nbt(
            &mut GzDecoder::new(&mut Cursor::new(&data)),
            Flavor::Uncompressed,
        )
        .expect("Alpha save NBT data")
        .0;

        let root: &NbtCompound = nbt.get(metadata::DATA).unwrap();

        let last_played: i64 = root.get(metadata::LAST_PLAYED).expect("LastPlayed value");
        let random_seed: i64 = root.get(metadata::RANDOM_SEED).expect("RandomSeed value");
        let size_on_disk: i64 = root.get(metadata::SIZE_ON_DISK).expect("SizeOnDisk value");
        let spawn_x: i32 = root.get(metadata::SPAWN_X).expect("SpawnX value");
        let spawn_y: i32 = root.get(metadata::SPAWN_Y).expect("SpawnY value");
        let spawn_z: i32 = root.get(metadata::SPAWN_Z).expect("SpawnZ value");
        let time: i64 = root.get(metadata::TIME).expect("Time value");

        let mut lvl = Level::new_with_name(level_name);
        lvl.time = time;
        lvl.set_spawn_point(spawn_x, spawn_y, spawn_z);
        lvl.custom_data
            .set_value::<i64>(metadata::LAST_PLAYED.to_string(), last_played);
        lvl.custom_data
            .set_value::<i64>(metadata::RANDOM_SEED.to_string(), random_seed);
        lvl.custom_data
            .set_value::<i64>(metadata::SIZE_ON_DISK.to_string(), size_on_disk);

        Ok(lvl)
    }

    #[allow(unused_variables)]
    fn write_alpha_level(&self, version: McVersion) -> Vec<u8> {
        let mut level_nbt = NbtCompound::new();
        let level_data = NbtCompound::new();

        // TODO: Player tag
        let last_played = level_nbt.insert(
            metadata::LAST_PLAYED,
            self.custom_data
                .get_value::<i64, &str>(metadata::LAST_PLAYED)
                .unwrap_or(
                    SystemTime::now()
                        .duration_since(UNIX_EPOCH)
                        .unwrap_or(Duration::new(0, 0))
                        .as_millis() as i64,
                ),
        );
        let random_seed = level_nbt.insert(
            metadata::RANDOM_SEED,
            self.custom_data
                .get_value::<i64, &str>(metadata::RANDOM_SEED)
                .unwrap_or(0),
        );
        let size_on_disk = level_nbt.insert(
            metadata::SIZE_ON_DISK,
            self.custom_data
                .get_value::<i64, &str>(metadata::SIZE_ON_DISK)
                .unwrap_or(0),
        );
        let spawn_x = level_nbt.insert(metadata::SPAWN_X, self.spawn.x);
        let spawn_y = level_nbt.insert(metadata::SPAWN_Y, self.spawn.y);
        let spawn_z = level_nbt.insert(metadata::SPAWN_Z, self.spawn.z);
        let time = level_nbt.insert(metadata::TIME, self.time);

        level_nbt.insert("Data", level_data);

        let mut data: Vec<u8> = Vec::new();

        write_nbt(&mut data, Some("Data"), &level_nbt, Flavor::GzCompressed)
            .expect("Failed to write NBT data to level.dat");

        data
    }
}
