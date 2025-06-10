use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::{CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::metadata;
use lodestone_level::level::Level;
use quartz_nbt::io::{self, Flavor};
use quartz_nbt::{NbtCompound, NbtList, NbtReprError};
use rayon::iter::IndexedParallelIterator;
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
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::GzCompressed)
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
                        let i = y as usize
                            + (z as usize * height as usize
                                + (x as usize * height as usize * length as usize));

                        // TODO: Fix
                        c.1.set_block(x, y, z, blocks[i] as u16)
                    }
                }
            }
        });

        Ok(level)
    }

    fn write_cw(&mut self) -> Vec<u8> {
        let mut out: Vec<u8> = Vec::new();

        let mut mclvl = NbtCompound::new();
        let mut created_by = NbtCompound::new();
        let mut map_generator = NbtCompound::new();
        let mut spawn_tag = NbtCompound::new();
        let entities = NbtList::new();
        let tile_entities = NbtList::new();

        let width = self.get_block_width() as usize;
        let height = self.get_block_height() as usize;
        let length = self.get_block_length() as usize;

        mclvl.insert("FormatVersion".to_string(), 1i8);
        mclvl.insert("Name".to_string(), &self.name);
        mclvl.insert("X".to_string(), width as i16);
        mclvl.insert("Y".to_string(), height as i16);
        mclvl.insert("Z".to_string(), length as i16);

        created_by.insert("Service".to_string(), "Project Lodestone");
        created_by.insert(
            "Username".to_string(),
            self.custom_data
                .get_value::<String, _>(metadata::AUTHOR)
                .unwrap_or("Unknown".to_string()),
        );

        mclvl.insert("CreatedBy".to_string(), created_by);

        map_generator.insert("Software".to_string(), "Unknown"); // todo: fill in with original version of mc it was generated with, or "Project Lodestone" if new.
        map_generator.insert("MapGeneratorName".to_string(), "Unknown");

        mclvl.insert("MapGenerator".to_string(), map_generator);

        mclvl.insert(
            "TimeCreated",
            self.custom_data
                .get_value::<i64, _>(metadata::CREATION_TIME)
                .unwrap_or(0),
        );
        mclvl.insert(
            "LastAccessed",
            self.custom_data
                .get_value::<i64, _>(metadata::LAST_ACCESSED)
                .unwrap_or(0),
        );
        mclvl.insert(
            "LastModified",
            self.custom_data
                .get_value::<i64, _>(metadata::LAST_MODIFIED)
                .unwrap_or(0),
        );

        spawn_tag.insert("X", self.spawn.x);
        spawn_tag.insert("Y", self.spawn.y);
        spawn_tag.insert("Z", self.spawn.z);

        spawn_tag.insert(
            "H",
            self.custom_data
                .get_value::<u8, _>(metadata::SPAWN_YAW)
                .unwrap_or(0),
        );
        spawn_tag.insert(
            "P",
            self.custom_data
                .get_value::<u8, _>(metadata::SPAWN_PITCH)
                .unwrap_or(0),
        );

        mclvl.insert("Spawn", spawn_tag);

        mclvl.insert("Entities".to_string(), entities);
        mclvl.insert("TileEntities".to_string(), tile_entities);

        let mut blocks = vec![0u8; width * length * height];

        let mx = self.get_min_block_x();
        let mz = self.get_min_block_z();

        blocks.par_iter_mut().enumerate().for_each(|(i, v)| {
            let y = i / (length * width);
            let z = (i / width) % length;
            let x = i % width;

            *v = self.get_block(x as i32 + mx, y as i16, z as i32 + mz) as u8;
        });

        mclvl.insert("BlockArray".to_string(), blocks);

        io::write_nbt(&mut out, Some("ClassicWorld"), &mclvl, Flavor::GzCompressed)
            .expect("Write compound");

        out
    }
}
