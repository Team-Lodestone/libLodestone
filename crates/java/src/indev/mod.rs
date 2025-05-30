use simdnbt::owned::{BaseNbt, Nbt, NbtCompound, NbtList, NbtTag};
use std::io::{Cursor, Write};
use std::time::SystemTime;
use wasm_bindgen::prelude::*;
use lodestone_level::level::chunk::Chunk;
use lodestone_level::level::level::{Coords, Level};

#[derive(Debug, Clone)]
pub struct IndevLevel {
    pub level: Level,
    pub environment: Environment,
    pub about: About
    // tile entities
    // entities
}

#[derive(Debug, Clone)]
pub struct Environment {
    pub time: i16,
    pub sky_brightness: i8,
    pub cloud_height: i16,
    pub cloud_color: i32,
    pub sky_color: i32,
    pub fog_color: i32,
    pub surrounding_ground_height: i16,
    pub surrounding_water_height: i16,
    pub surrounding_ground_type: i8,
    pub surrounding_water_type: i8
}


#[derive(Debug, Clone)]
pub struct About {
    pub author: String,
    pub created_on: i64
}

impl IndevLevel {

    pub fn new(height: i16, name: String, author: String) -> IndevLevel {
        IndevLevel {
            level: Level::new_with_name(name),
            // TODO: make this programmatic
            environment: Environment {
                time: 0,
                sky_brightness: 100,
                cloud_height: height - 64,
                cloud_color: 0xFFFFFF,
                sky_color: 0x99CCFF,
                fog_color: 0xFFFFFF,
                surrounding_ground_height: height / 2,
                surrounding_water_height: height / 2,
                surrounding_ground_type: 2,
                surrounding_water_type: 8,
            },
            about: About {
                author,
                created_on: SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).expect("Time since unix epoch").as_millis() as i64,
            }
        }
    }

    pub fn new_from_data(data: Vec<u8>) -> Result<IndevLevel, String> {
        let nbt = simdnbt::borrow::read(&mut Cursor::new(&data)).expect("Level NBT data").unwrap();

        let about = nbt.compound("About").expect("About compound tag");
        let environment = nbt.compound("Environment").expect("Environment compound tag");
        let map = nbt.compound("Map").expect("Map compound tag");
        let entities = nbt.list("Entities").expect("Entities tag");
        let tile_entities = nbt.list("TileEntities").expect("TileEntities tag");

        // About
        let author = about.string("Author").expect("Author tag").to_string();
        let name = about.string("Name").expect("Name tag").to_string();
        let created_on = about.long("CreatedOn").expect("Creation date tag");

        println!("author: {}, name: {}", author, name);

        // Environment
        let time = environment.short("TimeOfDay").expect("Time of day");
        let sky_brightness = environment.byte("SkyBrightness").expect("SkyBrightness tag");
        let cloud_height = environment.short("CloudHeight").expect("Cloud Height");
        let cloud_color = environment.int("CloudColor").expect("Cloud Color");
        let sky_color = environment.int("SkyColor").expect("Sky Color");
        let fog_color = environment.int("FogColor").expect("Fog Color");
        let surrounding_ground_height = environment.short("SurroundingGroundHeight").expect("SurroundingGroundHeight tag");
        let surrounding_water_height = environment.short("SurroundingWaterHeight").expect("SurroundingWaterHeight tag");
        let surrounding_ground_type = environment.byte("SurroundingGroundType").expect("SurroundingGroundType tag");
        let surrounding_water_type = environment.byte("SurroundingWaterType").expect("SurroundingWaterType tag");

        // Map
        let width: usize = map.short("Width").expect("Width tag") as usize;
        let length: usize = map.short("Length").expect("Length tag") as usize;
        let height: usize = map.short("Height").expect("Height tag") as usize;
        let spawn = map.list("Spawn").expect("Spawn tag").shorts().expect("Spawn shorts vec");
        let blocks = map.byte_array("Blocks").expect("Blocks tag").to_vec();
        let data = map.byte_array("Data").expect("Data tag").to_vec();

        // TODO: better impl for errors
        if blocks.len() != (width * length * height) {
            panic!("Read blocks does not match level dimensions!");
        }

        if data.len() != (width * length * height) {
            panic!("Read metadata does not match level dimensions!");
        }

        // Spawn
        let spawn_x = spawn[0];
        let spawn_y = spawn[1];
        let spawn_z = spawn[2];

        let mut level = Level::new_with_name(name);
        level.create_finite(width as i32, height as i16, length as i32);
        level.set_spawn_point(spawn_x, spawn_y, spawn_z);

        // again this is just meant to work at the moment, not be fast.
        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    let i = (y as usize) * ((length as usize) * (width as usize)) + (z as usize) * (width as usize) + (x as usize);

                    level.set_block(x as i32, y as i16, z as i32, blocks[i] as u16);
                    level.set_data(x as i32, y as i16, z as i32, data[i]);
                }
            }
        }

        let mcg = IndevLevel {
            level,
            environment: Environment {
                time,
                sky_brightness,
                cloud_height,
                cloud_color,
                sky_color,
                fog_color,
                surrounding_ground_height,
                surrounding_water_height,
                surrounding_ground_type,
                surrounding_water_type,
            },
            about: About {
                author,
                created_on,
            },
        };

        Ok(mcg)
    }

    // TODO
    // HACK: wasm won't let me take in &mut Vec<u8> so bub fix for now
    pub fn write(&mut self, compress: bool) -> Vec<u8> {
        let mut mclvl = NbtCompound::new();
        let mut about = NbtCompound::new();
        let mut env = NbtCompound::new();
        let mut map = NbtCompound::new();
        let mut entities = NbtList::Compound(Vec::new());
        let mut tile_entities = NbtList::Compound(Vec::new());

        let mut this = self.clone();

        // About
        about.insert("CreatedOn".to_string(), this.about.created_on);
        about.insert("Name".to_string(), (this.level.clone()).name);
        about.insert("Author".to_string(), this.about.author);

        // env
        env.insert("TimeOfDay".to_string(), this.environment.time);
        env.insert("SkyBrightness".to_string(), this.environment.sky_brightness);
        env.insert("SkyColor".to_string(), this.environment.sky_color);
        env.insert("FogColor".to_string(), this.environment.fog_color);
        env.insert("CloudColor".to_string(), this.environment.cloud_color);
        env.insert("CloudHeight".to_string(), this.environment.cloud_height);
        env.insert("SurroundingGroundType".to_string(), this.environment.surrounding_ground_type);
        env.insert("SurroundingGroundHeight".to_string(), this.environment.surrounding_ground_height);
        env.insert("SurroundingWaterType".to_string(), this.environment.surrounding_water_type);
        env.insert("SurroundingWaterHeight".to_string(), this.environment.surrounding_water_height);

        let width = this.level.get_block_width();
        let length = this.level.get_block_depth();
        let height = this.level.get_block_height();

        // map
        map.insert("Width".to_string(), width as i16);
        map.insert("Length".to_string(), length as i16);
        map.insert("Height".to_string(), height as i16);

        let mut sp = vec![0i16; 3];
        sp[0] = this.level.spawn.x;
        sp[1] = this.level.spawn.y;
        sp[2] = this.level.spawn.z;

        map.insert("Spawn".to_string(), NbtList::from(sp));

        let mut blocks: Vec<u8> = Vec::with_capacity((width as usize) * (length as usize) * (height as usize));
        blocks.resize((width as usize) * (length as usize) * (height as usize), 0);

        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    let i = (y as usize) * ((length as usize) * (width as usize)) + (z as usize) * (width as usize) + (x as usize);

                    blocks[i] = self.level.get_block(x, y, z) as u8;
                }
            }
        }



        map.insert("Blocks".to_string(), NbtTag::ByteArray(blocks));
        map.insert("Data".to_string(), NbtTag::ByteArray(Vec::new()));

        // MinecraftLevel
        mclvl.insert("About".to_string(), about);
        mclvl.insert("Environment".to_string(), env);
        mclvl.insert("Map".to_string(), map);

        mclvl.insert("Entities".to_string(), entities);
        mclvl.insert("TileEntities".to_string(), tile_entities);

        let nbt = Nbt::Some(BaseNbt::new(
            "MinecraftLevel",
            mclvl
        ));

        let mut out: Vec<u8> = Vec::new();
        nbt.write(&mut out);

        out
    }
}