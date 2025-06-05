use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::{CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::metadata;
use lodestone_level::level::Level;
use quartz_nbt::io::{self, Flavor};
use quartz_nbt::{NbtCompound, NbtList, NbtReprError, NbtTag};
use rayon::iter::IntoParallelRefMutIterator;
use rayon::iter::ParallelIterator;
use std::io::Cursor;

pub trait CWLevel {
    fn new_cw(height: i16, name: String, author: String) -> Level;
    fn read_cw(data: Vec<u8>) -> Result<Level, String>;
    fn write_cw(&mut self) -> Vec<u8>;
}

impl CWLevel for Level {
    fn new_cw(_height: i16, name: String, _author: String) -> Level {
        // TODO: impl with default values
        Level::new_with_name(name)
    }

    fn read_cw(data: Vec<u8>) -> Result<Level, String> {
        log::debug!("Reading compound");
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::Uncompressed)
            .expect("ClassicWorld NBT data")
            .0;

        log::debug!("Reading header");
        // let format_version: i8 = nbt.get("FormatVersion").expect("Level version");
        let name: &str = nbt.get("Name").unwrap_or("Unknown");
        // let uuid: &[u8] = nbt.get("UUID").expect("Level UUID");

        let width: i16 = nbt.get("X").expect("Level width");
        let height: i16 = nbt.get("Y").expect("Level height");
        let length: i16 = nbt.get("Z").expect("Level length");

        let created_by: Result<&NbtCompound, NbtReprError> = nbt.get("CreatedBy");

        let software: &str;
        let username: &str;

        match created_by {
            Ok(created) => {
                software = created.get("Software").unwrap_or("Unknown");
                username = created.get("Username").unwrap_or("Unknown");
            }
            Err(_) => {
                software = "Unknown";
                username = "Unknown";
            }
        }

        println!(
            "name: {}, username: {}, software: {}",
            name, username, software
        );

        let map_generator: Result<&NbtCompound, NbtReprError> = nbt.get("MapGenerator");

        let map_software: &str;
        let map_generator_name: &str;

        match map_generator {
            Ok(generator) => {
                map_software = generator.get("Software").unwrap_or("Unknown");
                map_generator_name = generator.get("MapGeneratorName").unwrap_or("Unknown");
            }
            Err(_) => {
                map_software = "Unknown";
                map_generator_name = "Unknown";
            }
        }

        println!(
            "map gen software: {}, map gen name: {}",
            map_software, map_generator_name
        );

        let time_created: i64 = nbt.get("TimeCreated").unwrap_or(0);
        let last_accessed: i64 = nbt.get("LastAccessed").unwrap_or(0);
        let last_modified: i64 = nbt.get("LastModified").unwrap_or(0);

        let spawn: Result<&NbtCompound, NbtReprError> = nbt.get("Spawn");

        let spawn_x: i16;
        let spawn_y: i16;
        let spawn_z: i16;
        let spawn_yaw: i8;
        let spawn_pitch: i8;

        match spawn {
            Ok(sp) => {
                spawn_x = sp.get("X").unwrap_or(0);
                spawn_y = sp.get("Y").unwrap_or(0);
                spawn_z = sp.get("Z").unwrap_or(0);
                spawn_yaw = sp.get("H").unwrap_or(0);
                spawn_pitch = sp.get("P").unwrap_or(0);
            }
            Err(_) => {
                spawn_x = 0;
                spawn_y = 0;
                spawn_z = 0;
                spawn_yaw = 0;
                spawn_pitch = 0;
            }
        }

        log::debug!("width: {}, height: {}, length: {}", width, height, length);
        log::debug!("Reading block array");

        let blocks: &[u8] = nbt.get("BlockArray").expect("Level blocks");

        log::debug!("Preparing level");
        let mut level = Level::new_with_name(name.to_owned());

        // TODO: store later
        // level.custom_data.set_value(metadata::UUID.to_string(), uuid);
        level
            .custom_data
            .set_value(metadata::LAST_MODIFIED.to_string(), last_modified);
        level
            .custom_data
            .set_value(metadata::LAST_ACCESSED.to_string(), last_accessed);
        level
            .custom_data
            .set_value(metadata::CREATION_TIME.to_string(), time_created);
        level
            .custom_data
            .set_value(metadata::SPAWN_YAW.to_string(), spawn_yaw);
        level
            .custom_data
            .set_value(metadata::SPAWN_PITCH.to_string(), spawn_pitch);

        log::debug!("Setting level spawn point");
        level.set_spawn_point(spawn_x, spawn_y, spawn_z);
        log::debug!("Creating chunks");
        log::debug!("Width: {}, Height: {}, Length: {}", width, height, length);
        level.create_finite(width as i32, height, length as i32);

        log::debug!("Read into chunks");
        // let s = Instant::now();
        let chunks = level.get_chunks_mut();

        let _ = chunks.par_iter_mut().for_each(|c| {
            for y in 0..height {
                for z in 0..CHUNK_LENGTH {
                    let lz = c.0.z * CHUNK_LENGTH as i32 + z as i32;
                    if lz >= length as i32 {
                        continue;
                    }

                    for x in 0..CHUNK_WIDTH {
                        let lx = c.0.x * CHUNK_WIDTH as i32 + x as i32;
                        if lx >= width as i32 {
                            continue;
                        }

                        // magic
                        let i = (y as usize) * (length as usize) * (width as usize)
                            + (lz as usize) * (width as usize)
                            + (lx as usize);

                        c.1.blocks[(y as usize)
                            + (z as usize) * (height as usize)
                            + (x as usize) * (height as usize) * CHUNK_LENGTH as usize] =
                            blocks[i] as u16;
                    }
                }
            }
        });

        Ok(level)
    }

    fn write_cw(&mut self) -> Vec<u8> {
        let mut mclvl = NbtCompound::new();
        let mut about = NbtCompound::new();
        let mut env = NbtCompound::new();
        let mut map = NbtCompound::new();
        let entities = NbtList::new();
        let tile_entities = NbtList::new();

        // About
        about.insert(
            "CreatedOn".to_string(),
            self.custom_data
                .get_value::<i64, _>(metadata::CREATION_TIME)
                .unwrap_or(0),
        );
        about.insert("Name".to_string(), self.clone().name);
        about.insert(
            "Author".to_string(),
            self.custom_data
                .get_value::<String, _>(metadata::AUTHOR)
                .unwrap_or("Player".to_string()),
        );

        // env
        env.insert("TimeOfDay".to_string(), self.time as i16);
        env.insert(
            "SkyBrightness".to_string(),
            self.custom_data
                .get_value::<i8, _>(metadata::SKY_BRIGHTNESS)
                .unwrap_or(15),
        );
        env.insert(
            "SkyColor".to_string(),
            self.custom_data
                .get_value::<i32, _>(metadata::SKY_COLOR)
                .unwrap_or(0x99CCFF),
        );
        env.insert(
            "FogColor".to_string(),
            self.custom_data
                .get_value::<i32, _>(metadata::FOG_COLOR)
                .unwrap_or(0xFFFFFF),
        );
        env.insert(
            "CloudColor".to_string(),
            self.custom_data
                .get_value::<i32, _>(metadata::CLOUD_COLOR)
                .unwrap_or(0xFFFFFF),
        );
        env.insert(
            "CloudHeight".to_string(),
            self.custom_data
                .get_value::<i16, _>(metadata::CLOUD_HEIGHT)
                .unwrap_or(self.get_max_block_y() / 2),
        );
        env.insert(
            "SurroundingGroundType".to_string(),
            self.custom_data
                .get_value::<i8, _>(metadata::SURROUNDING_GROUND_TYPE)
                .unwrap_or(2),
        );
        env.insert(
            "SurroundingGroundHeight".to_string(),
            self.custom_data
                .get_value::<i16, _>(metadata::SURROUNDING_GROUND_HEIGHT)
                .unwrap_or(self.get_max_block_y() / 3),
        );
        env.insert(
            "SurroundingWaterType".to_string(),
            self.custom_data
                .get_value::<i8, _>(metadata::SURROUNDING_WATER_TYPE)
                .unwrap_or(8),
        );
        env.insert(
            "SurroundingWaterHeight".to_string(),
            self.custom_data
                .get_value::<i16, _>(metadata::SURROUNDING_WATER_HEIGHT)
                .unwrap_or(self.get_max_block_y() / 2),
        );

        let width = self.get_max_block_x();
        let length = self.get_max_block_z();
        let height = self.get_max_block_y();

        // map
        map.insert("Width".to_string(), width as i16);
        map.insert("Length".to_string(), length as i16);
        map.insert("Height".to_string(), height);

        let mut sp = vec![0i16; 3];
        sp[0] = self.spawn.x;
        sp[1] = self.spawn.y;
        sp[2] = self.spawn.z;

        map.insert("Spawn".to_string(), NbtList::from(sp));

        let mut blocks: Vec<i8> =
            Vec::with_capacity((width as usize) * (length as usize) * (height as usize));
        blocks.resize((width as usize) * (length as usize) * (height as usize), 0);

        let mut data: Vec<i8> =
            Vec::with_capacity((width as usize) * (length as usize) * (height as usize));
        data.resize((width as usize) * (length as usize) * (height as usize), 0);

        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    let i = (y as usize) * ((length as usize) * (width as usize))
                        + (z as usize) * (width as usize)
                        + (x as usize);

                    blocks[i] = self.get_block(x, y, z) as i8;
                    data[i] = self.get_data(x, y, z) as i8;
                }
            }
        }

        map.insert("Blocks".to_string(), NbtTag::ByteArray(blocks));
        map.insert("Data".to_string(), NbtTag::ByteArray(data));

        // MinecraftLevel
        mclvl.insert("About".to_string(), about);
        mclvl.insert("Environment".to_string(), env);
        mclvl.insert("Map".to_string(), map);

        mclvl.insert("Entities".to_string(), entities);
        mclvl.insert("TileEntities".to_string(), tile_entities);

        let mut out: Vec<u8> = Vec::new();
        io::write_nbt(
            &mut out,
            Some("MinecraftLevel"),
            &mclvl,
            Flavor::Uncompressed,
        )
        .unwrap();

        out
    }
}
