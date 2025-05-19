use crate::java::classic::ClassicLevel;
use byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};
use std::io::{Cursor, Read, Write};
use simdnbt::borrow::NbtList;
use wasm_bindgen::prelude::*;

#[derive(Debug, Clone)]
#[wasm_bindgen(getter_with_clone)]
pub struct IndevLevel {
    pub environment: Environment,
    pub map: Map,
    pub about: About
    // tile entities
    // entities
}

#[derive(Debug, Clone)]
#[wasm_bindgen(getter_with_clone)]
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
#[wasm_bindgen(getter_with_clone)]
pub struct Map {
    pub blocks: Vec<u8>,
    pub data: Vec<u8>,
    pub width: i16,
    pub length: i16,
    pub height: i16,
    pub spawn: Spawn
}

#[derive(Debug, Clone)]
#[wasm_bindgen(getter_with_clone)]
pub struct About {
    pub author: String,
    pub name: String,
    pub created_on: i64
}


// By default Spawn is stored in a short array, but the array is always spawn coords XYZ so why not just make it a struct
#[derive(Debug, Clone)]
#[wasm_bindgen(getter_with_clone)]
pub struct Spawn {
    pub x: i16,
    pub y: i16,
    pub z: i16
}

#[wasm_bindgen]
impl IndevLevel {

    #[wasm_bindgen]
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
        let width = map.short("Width").expect("Width tag");
        let length = map.short("Length").expect("Length tag");
        let height = map.short("Height").expect("Height tag");
        let spawn = map.list("Spawn").expect("Spawn tag").shorts().expect("Spawn shorts vec");
        let blocks = map.byte_array("Blocks").expect("Blocks tag").to_vec();
        let data = map.byte_array("Data").expect("Data tag").to_vec();

        // Spawn
        let spawn_x = spawn[0];
        let spawn_y = spawn[1];
        let spawn_z = spawn[2];

        let mcg = IndevLevel {
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
            map: Map {
                blocks,
                data,
                width,
                length,
                height,
                spawn: Spawn {
                    x: spawn_x,
                    y: spawn_y,
                    z: spawn_z,
                },
            },
            about: About {
                author,
                name,
                created_on,
            },
        };

        Ok(mcg)
    }

    #[wasm_bindgen]
    pub fn write(&self, out: &mut [u8], compress: bool) {

    }
}