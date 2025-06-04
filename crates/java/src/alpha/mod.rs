use flate2::read::GzDecoder;
use flate2::write::GzEncoder;
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_common::types::hashmap_ext::Value::{Bool, Int64};
use lodestone_level::level::chunk::{Chunk, CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::{metadata, Coords, Level};
use quartz_nbt::io::{write_nbt, Flavor};
use quartz_nbt::{io, NbtCompound, NbtTag};
use std::fs;
use std::fs::File;
use std::io::{BufWriter, Cursor};
use std::path::Path;
use std::time::{Duration, SystemTime, UNIX_EPOCH};

pub trait AlphaLevel {
    fn new(name: String) -> Level;

    fn read_alpha_dir(path: &Path) -> Result<Level, String>;

    fn write_alpha_dir(&mut self, lvl: &Level, path: &Path) -> Vec<u8>;

    fn read_alpha_chunk(&mut self, path: &Path) -> Result<Chunk, String>;

    fn base36(n: u8) -> String;
}

impl AlphaLevel for Level {
    fn new(name: String) -> Level {
        Level::new_with_name(name)
    }

    fn read_alpha_dir(path: &Path) -> Result<Level, String> {
        log::debug!("Reading level.dat");
        let level_dat = path.join("level.dat");

        if !level_dat.exists() && !level_dat.is_file() {
            panic!("level.dat does not exist or is not a file!");
        }

        let data = fs::read(level_dat).map_err(|e| e.to_string())?;
        let nbt = io::read_nbt(
            &mut GzDecoder::new(&mut Cursor::new(&data)),
            Flavor::Uncompressed,
        )
        .expect("Alpha save NBT data")
        .0;

        let root: &NbtCompound = nbt.get("Data").unwrap();

        let last_played: i64 = root.get("LastPlayed").expect("LastPlayed value");
        let random_seed: i64 = root.get("RandomSeed").expect("RandomSeed value");
        let size_on_disk: i64 = root.get("SizeOnDisk").expect("SizeOnDisk value");
        let spawn_x: i32 = root.get("SpawnX").expect("SpawnX value");
        let spawn_y: i32 = root.get("SpawnY").expect("SpawnY value");
        let spawn_z: i32 = root.get("SpawnZ").expect("SpawnZ value");
        let time: i64 = root.get("Time").expect("Time value");

        let mut lvl = Level::new_with_name("World1".to_string());
        lvl.time = time;
        lvl.set_spawn_point(spawn_x as i16, spawn_y as i16, spawn_z as i16);
        lvl.custom_data
            .insert(metadata::LAST_PLAYED.to_string(), Int64(last_played));
        lvl.custom_data
            .insert(metadata::RANDOM_SEED.to_string(), Int64(random_seed));
        lvl.custom_data
            .insert(metadata::SIZE_ON_DISK.to_string(), Int64(size_on_disk));

        // Read all chunks
        for x in 0..63 {
            for z in 0..63 {
                let mut chunk_dir = path.join(Self::base36(x)).join(Self::base36(z));

                let _chunk = Self::read_alpha_chunk(&mut lvl, &mut chunk_dir)?;
            }
        }
        Ok(lvl)
    }

    #[allow(unused_variables)]
    fn write_alpha_dir(&mut self, lvl: &Level, path: &Path) -> Vec<u8> {
        let level_dat = path.join("level.dat");

        let mut level_nbt = NbtCompound::new();
        let level_data = NbtCompound::new();

        // TODO: Player tag
        let last_played = level_nbt.insert(
            metadata::LAST_PLAYED,
            lvl.custom_data
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
            lvl.custom_data
                .get_value::<i64, &str>(metadata::RANDOM_SEED)
                .unwrap_or(0),
        );
        let size_on_disk = level_nbt.insert(
            metadata::SIZE_ON_DISK,
            lvl.custom_data
                .get_value::<i64, &str>(metadata::SIZE_ON_DISK)
                .unwrap_or(0),
        );
        let spawn_x = level_nbt.insert(
            metadata::SPAWN_X,
            lvl.custom_data
                .get_value::<i64, &str>(metadata::SPAWN_X)
                .unwrap_or(0),
        );
        let spawn_y = level_nbt.insert(
            metadata::SPAWN_Y,
            lvl.custom_data
                .get_value::<i64, &str>(metadata::SPAWN_Y)
                .unwrap_or(64),
        );
        let spawn_z = level_nbt.insert(
            metadata::SPAWN_Z,
            lvl.custom_data
                .get_value::<i64, &str>(metadata::SPAWN_Z)
                .unwrap_or(0),
        );
        let time = level_nbt.insert(metadata::TIME, lvl.time);

        level_nbt.insert("Data", level_data);

        // Write level.dat
        let level_dat_file = File::create(level_dat).unwrap();
        let writer = BufWriter::new(level_dat_file);

        let mut gz = GzEncoder::new(writer, flate2::Compression::default());
        write_nbt(&mut gz, Some("Data"), &level_nbt, Flavor::Uncompressed)
            .expect("Failed to write NBT data to level.dat");

        todo!()
    }

    fn read_alpha_chunk(&mut self, path: &Path) -> Result<Chunk, String> {
        // Chunk dir does not exist
        if !path.exists() {
            return Err(format!("Alpha chunk does not exist {}", path.display()));
        }

        // Chunk dir is not a folder
        if !path.is_dir() {
            return Err("Chunk directory is not a directory! Ignoring.".to_string());
        }

        // Read all chunk files inside chunk_dir
        for entry in fs::read_dir(path).map_err(|e| e.to_string())? {
            let path = entry.map_err(|e| e.to_string())?.path();
            if !path.is_file() || !path.extension().map_or(false, |ext| ext == "dat") {
                continue;
            }

            // Parse NBT data in chunk_data
            let chunk_data = fs::read(path).map_err(|e| e.to_string())?;
            let chunk_nbt = io::read_nbt(&mut Cursor::new(&chunk_data), Flavor::GzCompressed)
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
            // Ignore heightmap
            let sky_light: &Vec<i8> = root.get("SkyLight").expect("SkyLight array");

            // Store chunk data into chunk
            let coords: Coords = Coords {
                x: chunk_x,
                z: chunk_z,
            };
            let mut chunk = Chunk::new(128);
            chunk
                .custom_data
                .insert(metadata::LAST_UPDATE.to_string(), Int64(last_update));
            chunk.custom_data.insert(
                metadata::TERRAIN_POPULATED.to_string(),
                Bool(terrain_populated),
            );

            // TODO: Batch this
            // TODO: Set state and lighting
            for y in 0..chunk.height {
                for x in 0..16 {
                    for z in 0..16 {
                        // Probably incorrect... this is what the wiki says.
                        let block_idx = y as usize
                            + (z * CHUNK_WIDTH as usize)
                            + (x * CHUNK_LENGTH as usize) * CHUNK_LENGTH as usize;

                        chunk.set_block(x as i8, y, z as i8, blocks[block_idx] as u16);
                        // chunk.set_state(x, y, z, data[i] as u8);
                        // chunk.set_light(SKY, x, y, z, sky_light[i] as u8);
                        // chunk.set_light(BLOCK, x, y, z, block_light[i] as u8);
                    }
                }
            }

            self.add_chunk(coords, chunk.clone());
            return Ok(chunk);
        }
        Err("No chunks found!".to_string())
    }

    fn base36(n: u8) -> String {
        format!("{:x}", n).to_lowercase()
    }
}
