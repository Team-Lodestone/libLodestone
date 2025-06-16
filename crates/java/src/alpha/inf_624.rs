use crate::alpha::AlphaLevel;
use byteorder::{BigEndian, ReadBytesExt};
use lodestone_common::types::hashmap_ext::HashMapExt;
use lodestone_level::level::chunk::{Chunk, CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::{metadata, Coords, Level};
use std::fs;
use std::fs::{create_dir_all, remove_dir_all, File};
use std::io::{BufWriter, Cursor, Read, Write};
use std::path::Path;

pub trait Infdev624Level {
    fn read_infdev_624_dir(path: &Path) -> Result<Level, String>;
    fn read_infdev_624_zone(lvl: &mut Level, data: Vec<u8>);
    fn write_infdev_624_dir(&mut self, path: &Path);
    fn write_infdev_624_zone(&self, coords: &Coords) -> Vec<u8>;
}

impl Infdev624Level for Level {
    fn read_infdev_624_dir(path: &Path) -> Result<Level, String> {
        if !path.exists() {
            return Err("Level directory does not exist!".into());
        }

        let level_dat = path.join("level.dat");
        let level_name = path
            .file_name()
            .unwrap()
            .to_str()
            .unwrap_or("World1")
            .to_string();
        let data = fs::read(level_dat).map_err(|e| e.to_string())?;
        let mut lvl = Level::read_alpha_level(level_name, data)
            .expect("Failed to parse Infdev 20100624 level.dat!");

        let data_dir = path.join("data");

        // Read zones
        for entry in fs::read_dir(data_dir).map_err(|e| e.to_string())? {
            match entry {
                Ok(entry) => {
                    let path = entry.path();
                    if path
                        .file_name()
                        .unwrap()
                        .to_str()
                        .unwrap()
                        .starts_with("zone_")
                    {
                        println!("Reading zone: {}", path.display());
                        let data = fs::read(&path).map_err(|e| e.to_string())?;
                        Self::read_infdev_624_zone(&mut lvl, data);
                    }

                    // Why Notch??
                    if path.starts_with("entities_") {}
                }
                Err(_) => {
                    continue;
                }
            }
        }

        Ok(lvl)
    }

    fn read_infdev_624_zone(lvl: &mut Level, data: Vec<u8>) {
        let mut c = Cursor::new(&data);
        let magic = c.read_u32::<BigEndian>().expect("Failed to read magic!");

        // 13 73 70 00
        if magic != 326332416 {
            panic!("Magic mismatch!");
        }

        let version = c.read_u16::<BigEndian>().expect("Failed to read version!");
        if version != 0 {
            panic!("Version mismatch! Infdev 20100624 only supports Zones with version 0!");
        }
        let slot_count = c
            .read_u16::<BigEndian>()
            .expect("Failed to read slot count!");

        let mut slots: Vec<u16> = vec![0u16; slot_count as usize];
        for i in 0..slot_count {
            slots[i as usize] = c
                .read_u16::<BigEndian>()
                .expect("Failed to read slot count!");
        }

        let original_position = c.position();
        for slot in slots {
            // Why???
            let read_position = slot as u64 * (32768 * 3 + 256) + 4096;
            if read_position < data.len() as u64 {
                c.set_position(read_position);
            } else {
                continue;
            }

            let chunk_x = c.read_i32::<BigEndian>().expect("Failed to read chunk X!");
            let chunk_z = c.read_i32::<BigEndian>().expect("Failed to read chunk Z!");
            let _time = c.read_i64::<BigEndian>().expect("Failed to read time!");
            let is_populated = c
                .read_i64::<BigEndian>()
                .expect("Failed to read is_populated!");

            c.set_position(read_position);

            let mut unknown: Vec<u8> = vec![0u8; 256];
            c.read_exact(&mut unknown)
                .expect("Failed to parse unknown field!");

            let mut blocks: Vec<u8> = vec![0u8; 32768];
            c.read_exact(&mut blocks)
                .expect("Failed to read block IDs!");

            let mut data: Vec<u8> = vec![0u8; 16384];
            c.read_exact(&mut data).expect("Failed to read metadata!");

            let mut sky_light: Vec<u8> = vec![0u8; 16384];
            c.read_exact(&mut sky_light)
                .expect("Failed to read sky light!");

            let mut block_light: Vec<u8> = vec![0u8; 16384];
            c.read_exact(&mut block_light)
                .expect("Failed to read block light!");

            let mut height_map: Vec<u8> = vec![0u8; 256];
            c.read_exact(&mut height_map)
                .expect("Failed to read height map!");

            let is_terrain_populated = (is_populated & 1) != 0;

            let mut chunk = Chunk::new(128);
            chunk.custom_data.set_value(
                metadata::TERRAIN_POPULATED.to_string(),
                is_terrain_populated,
            );

            let height = 128usize;
            for y in 0..height {
                for z in 0..CHUNK_LENGTH as usize {
                    for x in 0..CHUNK_WIDTH as usize {
                        let i = y + (z * height + (x * height * CHUNK_LENGTH as usize));

                        let block_id = blocks[i] as u16;
                        if block_id != 0 {
                            chunk.get_or_create_chunk_section_mut(y as i16);
                            chunk.set_block(x as i8, y as i16, z as i8, blocks[i] as u16);
                        }
                    }
                }
            }
            lvl.add_chunk(
                Coords {
                    x: chunk_x,
                    z: chunk_z,
                },
                chunk,
            );
        }
        c.set_position(original_position);
    }

    fn write_infdev_624_dir(&mut self, path: &Path) {
        if path.exists() {
            remove_dir_all(path).expect("Failed to remove output directories before writing!");
        }
        create_dir_all(path).expect("Failed to create output directories!");

        let level_dat = path.join("level.dat");
        let level_dat_file = if level_dat.exists() {
            File::open(&level_dat).expect("Failed to open level.dat!")
        } else {
            File::create(&level_dat).expect("Failed to create level.dat!")
        };
        let level_data = Level::write_alpha_level(self);
        let mut writer = BufWriter::new(level_dat_file);
        writer
            .write_all(&level_data)
            .expect("Could not write to level.dat!");
        writer.flush().expect("Could not flush level.dat!");

        let data_dir = path.join("data");
    }

    fn write_infdev_624_zone(&self, coords: &Coords) -> Vec<u8> {
        todo!()
    }
}

fn get_xz_shifted(mut x: i32, mut z: i32) -> i32 {
    let shifted_x = x >> 5;
    let shifted_z = z >> 5;
    x -= shifted_x << 5;
    z -= shifted_z << 5;

    x + (z << 5)
}
