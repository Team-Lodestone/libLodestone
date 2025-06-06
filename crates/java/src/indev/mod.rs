use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::{CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::metadata;
use lodestone_level::level::Level;
use quartz_nbt::io::{self, Flavor};
use quartz_nbt::{NbtCompound, NbtList, NbtTag};
use rayon::iter::IntoParallelRefMutIterator;
use rayon::iter::ParallelIterator;
use std::io::Cursor;

pub trait IndevLevel {
    fn new_indev(height: i16, name: String, author: String) -> Level;
    fn read_indev(data: Vec<u8>) -> Result<Level, String>;
    fn write_indev(&mut self, out: &mut Vec<u8>);
}

impl IndevLevel for Level {
    fn new_indev(_height: i16, name: String, _author: String) -> Level {
        // TODO: impl with default values
        Level::new_with_name(name)
    }

    fn read_indev(data: Vec<u8>) -> Result<Level, String> {
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::GzCompressed)
            .expect("Level NBT data")
            .0;

        let about: &NbtCompound = nbt.get("About").expect("About compound");
        let environment: &NbtCompound = nbt.get("Environment").expect("Environment compound");
        let map: &NbtCompound = nbt.get("Map").expect("Map compound");
        // let entities: &NbtList = nbt.get("Entities").expect("Entities compound list");
        // let tile_entities: &NbtList = nbt.get("TileEntities").expect("TileEntities compound list");

        // About
        let author: &str = about.get("Author").expect("Author string");
        let name: &str = about.get("Name").expect("Name string");
        let created_on: i64 = about.get("CreatedOn").expect("CreatedOn i64");

        println!("author: {}, name: {}", author, name);

        // Environment
        let time: i16 = environment.get("TimeOfDay").expect("Time of day");
        let sky_brightness: i8 = environment.get("SkyBrightness").expect("SkyBrightness tag");
        let cloud_height: i16 = environment.get("CloudHeight").expect("Cloud Height");
        let cloud_color: i32 = environment.get("CloudColor").expect("Cloud Color");
        let sky_color: i32 = environment.get("SkyColor").expect("Sky Color");
        let fog_color: i32 = environment.get("FogColor").expect("Fog Color");
        let surrounding_ground_height: i16 = environment
            .get("SurroundingGroundHeight")
            .expect("SurroundingGroundHeight tag");
        let surrounding_water_height: i16 = environment
            .get("SurroundingWaterHeight")
            .expect("SurroundingWaterHeight tag");
        let surrounding_ground_type: i8 = environment
            .get("SurroundingGroundType")
            .expect("SurroundingGroundType tag");
        let surrounding_water_type: i8 = environment
            .get("SurroundingWaterType")
            .expect("SurroundingWaterType tag");

        // Map
        let width: i16 = map.get("Width").expect("Width tag");
        let length: i16 = map.get("Length").expect("Length tag");
        let height: i16 = map.get("Height").expect("Height tag");
        let spawn: &NbtList = map.get("Spawn").expect("Spawn tag");
        let blocks: &[u8] = map.get("Blocks").expect("Blocks tag");
        // let data: &[u8] = map.get("Data").expect("Data tag");

        // // TODO: better impl for errors
        // if blocks.len() != (width * length * height) {
        //     panic!("Read blocks does not match level dimensions!");
        // }

        // if data.len() != (width * length * height) {
        //     panic!("Read metadata does not match level dimensions!");
        // }

        let mut level = Level::new_with_name(name.to_owned());

        // Spawn
        let NbtTag::Short(spawn_x) = spawn[0] else {
            panic!("spawn_x was not a short")
        }; // can't we just do .expect?
        let NbtTag::Short(spawn_y) = spawn[1] else {
            panic!("spawn_y was not a short")
        };
        let NbtTag::Short(spawn_z) = spawn[2] else {
            panic!("spawn_z was not a short")
        };

        level.set_spawn_point(spawn_x, spawn_y, spawn_z);
        level.create_finite(width as i32, height, length as i32);

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

                        c.1.set_block(x, y, z, blocks[i] as u16)
                    }
                }
            }
        });

        // About
        level
            .custom_data
            .set_value(metadata::CREATION_TIME.to_string(), created_on);
        level.name = name.to_string();
        level
            .custom_data
            .set_value(metadata::AUTHOR.to_string(), author.to_string());
        // Environment
        level.time = time as i64;
        level
            .custom_data
            .set_value(metadata::SKY_BRIGHTNESS.to_string(), sky_brightness);
        level
            .custom_data
            .set_value(metadata::SKY_COLOR.to_string(), sky_color);
        level
            .custom_data
            .set_value(metadata::FOG_COLOR.to_string(), fog_color);
        level
            .custom_data
            .set_value(metadata::CLOUD_COLOR.to_string(), cloud_color);
        level
            .custom_data
            .set_value(metadata::CLOUD_HEIGHT.to_string(), cloud_height);
        level.custom_data.set_value(
            metadata::SURROUNDING_GROUND_TYPE.to_string(),
            surrounding_ground_type,
        );
        level.custom_data.set_value(
            metadata::SURROUNDING_GROUND_HEIGHT.to_string(),
            surrounding_ground_height,
        );
        level.custom_data.set_value(
            metadata::SURROUNDING_WATER_TYPE.to_string(),
            surrounding_water_type,
        );
        level.custom_data.set_value(
            metadata::SURROUNDING_WATER_HEIGHT.to_string(),
            surrounding_water_height,
        );

        Ok(level)
    }

    fn write_indev(&mut self, out: &mut Vec<u8>) {
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

        let width = self.get_block_width();
        let length = self.get_block_length();
        let height = self.get_block_height();

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

        let mx = self.get_min_block_x();
        let mz = self.get_min_block_z();

        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    blocks[(y as usize) * (length as usize * width as usize)
                        + (z as usize) * (width as usize)
                        + (x as usize)] =
                        self.get_block(x as i32 + mx, y as i16, z as i32 + mz) as i8;
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

        io::write_nbt(out, Some("MinecraftLevel"), &mclvl, Flavor::GzCompressed).unwrap();
    }
}
