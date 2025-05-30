use quartz_nbt::io::{self, Flavor};
use quartz_nbt::{NbtTag, NbtCompound, NbtList};
use std::io::{Cursor, Write};
use std::time::SystemTime;
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
        let nbt = io::read_nbt(&mut Cursor::new(&data), Flavor::Uncompressed)
            .expect("Level NBT data")
            .0;

        let about:         &NbtCompound = nbt.get("About")       .expect("About compound");
        let environment:   &NbtCompound = nbt.get("Environment") .expect("Environment compound");
        let map:           &NbtCompound = nbt.get("Map")         .expect("Map compound");
        let entities:      &NbtCompound = nbt.get("Entities")    .expect("Entities compound");
        let tile_entities: &NbtCompound = nbt.get("TileEntities").expect("TileEntities compound");

        // About
        let author:         &str         = nbt.get("Author")      .expect("Author string");
        let name:           &str         = nbt.get("Name")        .expect("Name string");
        let created_on:     i64          = nbt.get("CreatedOn")   .expect("CreatedOn i64");

        println!("author: {}, name: {}", author, name);

        // Environment
        let time:                      i16 = environment.get("TimeOfDay")    .expect("Time of day");
        let sky_brightness:             i8 = environment.get("SkyBrightness").expect("SkyBrightness tag");
        let cloud_height:              i16 = environment.get("CloudHeight")  .expect("Cloud Height");
        let cloud_color:               i32 = environment.get("CloudColor")   .expect("Cloud Color");
        let sky_color:                 i32 = environment.get("SkyColor")     .expect("Sky Color");
        let fog_color:                 i32 = environment.get("FogColor")     .expect("Fog Color");
        let surrounding_ground_height: i16 = environment
            .get("SurroundingGroundHeight")
            .expect("SurroundingGroundHeight tag");
        let surrounding_water_height:  i16 = environment
            .get("SurroundingWaterHeight")
            .expect("SurroundingWaterHeight tag");
        let surrounding_ground_type:    i8 = environment
            .get("SurroundingGroundType")
            .expect("SurroundingGroundType tag");
        let surrounding_water_type:     i8 = environment
            .get("SurroundingWaterType")
            .expect("SurroundingWaterType tag");

        // Map
        let width:      i16 = map.get("Width").expect("Width tag");
        let length:     i16 = map.get("Length").expect("Length tag");
        let height:     i16 = map.get("Height").expect("Height tag");
        let spawn: &NbtList = map.get("Spawn").expect("Spawn tag");
        let blocks:   &[u8] = map.get("Blocks").expect("Blocks tag");
        let data:     &[u8] = map.get("Data").expect("Data tag");

        // // TODO: better impl for errors
        // if blocks.len() != (width * length * height) {
        //     panic!("Read blocks does not match level dimensions!");
        // }

        // if data.len() != (width * length * height) {
        //     panic!("Read metadata does not match level dimensions!");
        // }

        // Spawn
        let NbtTag::Short(spawn_x) = spawn[0] else { panic!("spawn_x was not a short") };
        let NbtTag::Short(spawn_y) = spawn[1] else { panic!("spawn_y was not a short") };
        let NbtTag::Short(spawn_z) = spawn[2] else { panic!("spawn_z was not a short") };

        let mut level = Level::new_with_name(name.to_owned());

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
                author: author.to_owned(),
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
        let mut entities = NbtList::new();
        let mut tile_entities = NbtList::new();

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

        let mut blocks: Vec<i8> = Vec::with_capacity((width as usize) * (length as usize) * (height as usize));
        blocks.resize((width as usize) * (length as usize) * (height as usize), 0);

        for y in 0..height {
            for z in 0..length {
                for x in 0..width {
                    let i = (y as usize) * ((length as usize) * (width as usize)) + (z as usize) * (width as usize) + (x as usize);

                    blocks[i] = self.level.get_block(x, y, z) as i8;
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

        let mut out: Vec<u8> = Vec::new();
        io::write_nbt(&mut out, Some("MinecraftLevel"), &mclvl, Flavor::Uncompressed).unwrap();

        out
    }
}
