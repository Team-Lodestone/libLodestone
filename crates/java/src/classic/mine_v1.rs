use lodestone_level::level::chunk::{CHUNK_LENGTH, CHUNK_WIDTH};
use lodestone_level::level::Level;
use rayon::iter::IndexedParallelIterator;
use rayon::iter::IntoParallelRefMutIterator;
use rayon::iter::ParallelIterator;

pub trait MineV1Level {
    fn read_minev1(data: Vec<u8>) -> Result<Level, String>;
    fn write_minev1(&self) -> Vec<u8>;
    fn get_minev1_file_size() -> usize;
}

impl MineV1Level for Level {
    fn read_minev1(data: Vec<u8>) -> Result<Level, String> {
        let mut level = Level::new();
        level.create_finite(256, 64, 256);

        let chunks = level.get_chunks_mut();

        let _ = chunks.par_iter_mut().for_each(|c| {
            for y in 0..64 {
                for z in 0..CHUNK_LENGTH {
                    let lz = c.0.z * CHUNK_LENGTH as i32 + z as i32;
                    if lz >= 256i32 {
                        continue;
                    }

                    for x in 0..CHUNK_WIDTH {
                        let lx = c.0.x * CHUNK_WIDTH as i32 + x as i32;
                        if lx >= 256i32 {
                            continue;
                        }

                        // magic
                        let i = (y as usize) * (256usize) * (256usize)
                            + (lz as usize) * (256usize)
                            + (lx as usize);

                        c.1.set_block(x, y, z, data[i] as u16)
                    }
                }
            }
        });

        Ok(level)
    }

    fn write_minev1(&self) -> Vec<u8> {
        let width = self.get_block_width() as usize;
        let length = self.get_block_length();
        let height = self.get_block_height() as usize;

        if width > 256 || length > 256 || height > 256 {
            println!(
                "WARN: Level bounds are too large for .mine v1's limited size of 256x64x256 (XYZ). Your level size is X: {}, Y: {}, Z: {}",
                width, height, length
            );
            println!("The level will be truncated to fit within these strict bounds.");
        }

        let mut blocks = vec![0u8; Self::get_minev1_file_size()];

        // TODO: block conversion map (later)
        blocks.par_iter_mut().enumerate().for_each(|(i, v)| {
            let y = i / (256 * 256);
            let z = (i / 256) % 256;
            let x = i % 256;

            *v = self.get_block(x as i32, y as i16, z as i32) as u8;
        });

        blocks
    }

    fn get_minev1_file_size() -> usize {
        256 * 64 * 256 // locked to this
    }
}
