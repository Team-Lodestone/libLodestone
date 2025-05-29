use simdnbt::owned::{BaseNbt, Nbt, NbtCompound, NbtList, NbtTag};
use std::io::{Cursor, Write};
use std::time::SystemTime;
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

    // TODO: Resizing
    pub fn set_block(&mut self, x: i16, y: i16, z: i16, block: u8) {
        let i = self.get_index(x, y, z);

        self.map.blocks[i] = block;
    }

    pub fn get_block(&self, x: i16, y: i16, z: i16, block: u8) -> u8 {
        let i = self.get_index(x, y, z);

        self.map.blocks[i]
    }

    pub fn new(width: i16, height: i16, length: i16, name: String, author: String) -> IndevLevel {
        IndevLevel {
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
            map: Map {
                blocks: vec![0u8; (width as usize) * (length as usize) * (height as usize)],
                data: vec![0u8; (width as usize) * (length as usize) * (height as usize)],
                width,
                length,
                height,
                spawn: Spawn {
                    x: width / 2,
                    y: height / 2,
                    z: length / 2
                },
            },
            about: About {
                author,
                name,
                created_on: SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).expect("Time since unix epoch").as_millis() as i64,
            }
        }
    }

    pub fn set_block_data(&mut self, x: i16, y: i16, z: i16, data: u8) {
        let i = self.get_index(x, y, z);

        self.map.data[i] = (self.map.data[i] & 0x0F) | ((data & 0x0F) << 4);
    }

    #[wasm_bindgen]
    pub fn resize(&mut self, width: i16, depth: i16, height: i16) {
        if width % 2 != 0 || height % 2 != 0 || depth % 2 != 0 {
            panic!("It seems Indev world sizes must be a power of 2, otherwise the game will index out of bounds.");
        }

        // old size
        let x0 = self.map.width as usize;
        let y0 = self.map.height as usize;
        let z0 = self.map.length as usize;

        // new size
        let x1 = width as usize;
        let y1 = height as usize;
        let z1 = depth as usize;

        let mut blocks = vec![0u8; x1 * y1 * z1];
        let mut data = vec![0u8; x1 * y1 * z1];

        for x in 0..x0.min(x1) {
            for y in 0..y0.min(y1) {
                for z in 0..z0.min(z1) {
                    let p0 = (y * z0 + z) * x0 + x; // old
                    let p1 = (y * z1 + z) * x1 + x; // new
                    blocks[p1] = self.map.blocks[p0];
                    data[p1] = self.map.data[p0];
                }
            }
        }

        if self.map.spawn.x > width || self.map.spawn.x < width {
            self.map.spawn.x = width / 2;
        }

        if self.map.spawn.y > height || self.map.spawn.y < height {
            self.map.spawn.y = height / 2;
        }

        if self.map.spawn.z > depth || self.map.spawn.z < depth {
            self.map.spawn.z = depth / 2;
        }

        self.map.blocks = blocks;
        self.map.data   = data;
        self.map.width  = width;
        self.map.height = height;
        self.map.length = depth;
    }

    pub fn set_spawn_point(&mut self, x: i16, y: i16, z: i16) {
        self.map.spawn.x = x;
        self.map.spawn.y = y;
        self.map.spawn.z = z;
    }

    pub fn set_block_light_level(&mut self, x: i16, y: i16, z: i16, level: u8) {
        let i = self.get_index(x, y, z);

        if (level > 15) {
            panic!("Light level out of range");
        }

        self.map.data[i] = (self.map.data[i] & 0xF0) | (level & 0x0F);
    }

    pub fn get_block_data(&mut self, x: i16, y: i16, z: i16) -> u8 {
        let i = self.get_index(x, y, z);

        (self.map.data[i] >> 4) & 0x0F
    }

    pub fn get_block_light_level(&mut self, x: i16, y: i16, z: i16) -> u8 {
        let i = self.get_index(x, y, z);

        self.map.data[i] & 0x0F
    }

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

    // TODO
    // HACK: wasm won't let me take in &mut Vec<u8> so bub fix for now
    pub fn write(&self, compress: bool) -> Vec<u8> {
        let mut mclvl = NbtCompound::new();
        let mut about = NbtCompound::new();
        let mut env = NbtCompound::new();
        let mut map = NbtCompound::new();
        let mut entities = NbtList::Compound(Vec::new());
        let mut tile_entities = NbtList::Compound(Vec::new());

        let this = self.clone();


        // About
        about.insert("CreatedOn".to_string(), this.about.created_on);
        about.insert("Name".to_string(), this.about.name);
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

        // map
        map.insert("Width".to_string(), this.map.width);
        map.insert("Length".to_string(), this.map.length);
        map.insert("Height".to_string(), this.map.height);

        let mut sp = vec![0i16; 3];
        sp[0] = this.map.spawn.x;
        sp[1] = this.map.spawn.y;
        sp[2] = this.map.spawn.z;

        map.insert("Spawn".to_string(), NbtList::from(sp));

        map.insert("Blocks".to_string(), NbtTag::ByteArray(this.map.blocks));
        map.insert("Data".to_string(), NbtTag::ByteArray(this.map.data));

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

    #[wasm_bindgen]
    pub fn get_index(&self, x: i16, y: i16, z: i16) -> usize {
        // our coords
        let x = x as usize;
        let y = y as usize;
        let z = z as usize;

        // world size
        let w = self.map.width as usize;
        let h = self.map.height as usize;
        let d = self.map.length as usize;

        if x < 0 || y < 0 || z < 0 ||
            x >= w || y >= h || z >= d {
            return !0;
        }

        (y * d + z) * w + x
    }
}