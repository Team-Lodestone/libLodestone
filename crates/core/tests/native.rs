#![cfg(target_arch = "x86_64")]

#[cfg(test)]
#[allow(dead_code)]
mod tests {
    use flate2::write::GzEncoder;
    use flate2::Compression;
    use lodestone_java;
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_java::anvil::Anvil;
    use lodestone_java::classic::classic_world::CWLevel;
    use lodestone_java::classic::mine_v2::MineV2Level;
    use lodestone_java::mcregion::Region;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::File;
    use std::io::{Read, Write};
    use std::path::Path;

    // #[test]
    fn mcg_level() {
        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let data = match fs::read("D:\\Home\\Downloads\\download(40).dat") {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let mut mcg = lodestone_java::classic::mcgalaxy_lvl::MCGLevel::new_from_data(data).unwrap();

        // can't be bothered to figure out a good way to do this...
        // although I can already think of just putting in a `get_size` method in every Level impl.
        let mut out = vec![0u8; (1024 * 512 * 1024) + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1];

        // resize
        mcg.classic_level.resize(1024, 1024, 512);
        mcg.write(&mut out);

        let mut enc = GzEncoder::new(Vec::new(), Compression::default());
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        let mut of = File::create("mcgOut.lvl").unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }

    // #[test]
    fn indev_level() {
        // ignore weird path, for testing on local machine
        let data = match fs::read("D:\\Home\\Downloads\\Indev World Backup") {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        // let indev = lodestone_java::indev::IndevLevel::new_from_data(data).unwrap();

        // // can't be bothered to figure out a good way to do this...
        // // although I can already think of just putting in a `get_size` method in every Level impl.
        // let mut out = vec![0u8; (1024 * 512 * 1024) + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1];
        //
        // // resize
        // mcg.classic_level.resize(1024, 1024, 512);
        // mcg.write(&mut out);
        //
        // let mut enc = GzEncoder::new(Vec::new(), Compression::default());
        // enc.write_all(&out).unwrap();
        // let c = enc.finish().unwrap();
        //
        // let mut of = File::create("mcgOut.lvl").unwrap();
        // of.write_all(&c).unwrap();
        // of.flush().unwrap();
    }

    // #[test]
    /*fn in_to_mcg() {
        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let fname = "Indev World Backup";

        let data = match fs::read(format!("D:\\Home\\Downloads\\{}", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let indev = lodestone_java::indev::IndevLevel::new_from_data(data).unwrap();

        let mut mcg = lodestone_java::classic::mcgalaxy_lvl::MCGLevel::new(indev.map.width, indev.map.height, indev.map.length, indev.map.spawn.x, indev.map.spawn.y, indev.map.spawn.z, 0, 0, 0, 0);

        mcg.classic_level.blocks = indev.map.blocks; // literally the same pretty much

        // can't be bothered to figure out a good way to do this...
        // although I can already think of just putting in a `get_size` method in every Level impl.
        let mut out = vec![0u8; 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + mcg.classic_level.blocks.len() + mcg.calc_section_length()];

        mcg.write(&mut out);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("test/lvl/dst/{}.lvl", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }*/

    #[test]
    fn region_folder_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let mut level = Level::new();

        println!("Reading level");
        // https://stackoverflow.com/questions/76955637/rust-iterate-through-a-folder-and-open-each-file
        let path = "../../test/regions/src/omni_beta/";
        let entries = fs::read_dir(path).unwrap();
        for entry in entries {
            match entry {
                Ok(entry) => {
                    println!("Processing region: {:?}", entry);
                    let file = File::open(entry.path());
                    match file {
                        Ok(mut file) => {
                            let mut buffer = Vec::new();
                            let content = file.read_to_end(&mut buffer);
                            match content {
                                Ok(_sz) => {
                                    level.read_mcr_into_existing(buffer);
                                }
                                Err(e) => {
                                    println!("  read error: {:?}", e);
                                }
                            }
                        }
                        Err(e) => {
                            println!("  open error: {:?}", e);
                        }
                    }
                }
                Err(e) => {
                    println!("  entry error: {:?}", e);
                }
            }
        }

        println!(
            "World bounds (XYZ): {}x{}x{}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        // println!("Generating blockmap");
        // let blockmap = level.get_blockmap();

        let map = level.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!("../../test/map/{}-{}_{}.raw", "RegionTest", level.get_block_width(), level.get_block_length())).unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();

        // let mut out = vec![0u8; level.get_minev2_file_size()];
        // level.write_minev2(&mut out);
        //
        // // why does this part take so damn long?
        // println!("Compressing");
        // let mut enc = GzEncoder::new(
        //     Vec::with_capacity(level.get_minev2_file_size()),
        //     Compression::fast(),
        // );
        // enc.write_all(&out).unwrap();
        // let c = enc.finish().unwrap();
        //
        // println!("Writing");
        // let mut of =
        //     File::create(format!("../../test/indev/dst/{}.mcworld", "level_test")).unwrap();
        // of.write_all(&c).unwrap();
        // of.flush().unwrap();

        // let mut of2 = File::create(format!("../../test/regions/dst/{}_blockmap.dat", "level_test")).unwrap();
        // of2.write_all(cast_slice(blockmap.as_slice())).unwrap();
        // of2.flush().unwrap();
    }

    // #[test]
    fn minev2_to_mcr_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "Main 3";

        println!("Reading file");
        let data = match fs::read(format!("../../test/cw/src/{}.cw", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        let mut mv2 = Level::read_cw(data).unwrap();
        // let mut mv2 = lodestone_level::level::Level::read_minev2(data).unwrap();
        // println!("Generating blockmap");
        // let blockmap = mv2.get_blockmap();

        let mut out = Vec::new();
        mv2.write_mcr(&mut out);

        // // why does this part take so damn long?
        // println!("Compressing");
        // let mut enc = GzEncoder::new(Vec::with_capacity(mv2.get_minev2_file_size()), Compression::fast());
        // enc.write_all(&out).unwrap();
        // let c = enc.finish().unwrap();
        //
        println!("Writing");
        let mut of = File::create(format!("../../test/regions/dst/{}.mcr", fname)).unwrap();
        of.write_all(&out).unwrap();
        of.flush().unwrap();
        //
        // let mut of2 = File::create(format!("../../test/regions/dst/{}_blockmap.dat", fname)).unwrap();
        // of2.write_all(cast_slice(blockmap.as_slice())).unwrap();
        // of2.flush().unwrap();
    }

    // #[test]
    fn mine_v2_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "13a_03-level_greffen";

        println!("Reading file");
        let data = match fs::read(format!("../../test/minev2/src/{}.mine", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        // let mut mv2 = lodestone_level::level::Level::read_cw(data).unwrap();
        let mut mv2 = Level::read_minev2(data).unwrap();
        // println!("Generating blockmap");
        // let blockmap = mv2.get_blockmap();

        let mut out = vec![0u8; mv2.get_minev2_file_size()];
        mv2.write_minev2(&mut out);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(
            Vec::with_capacity(mv2.get_minev2_file_size()),
            Compression::fast(),
        );
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("../../test/minev2/dst/{}.mine", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
        //
        // let mut of2 = File::create(format!("../../test/regions/dst/{}_blockmap.dat", fname)).unwrap();
        // of2.write_all(cast_slice(blockmap.as_slice())).unwrap();
        // of2.flush().unwrap();
    }

    // #[test]
    fn mca_to_minev2_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "r.0.0";

        println!("Reading file");
        let data = match fs::read(format!("../../test/anvil/src/{}.mca", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        // let mut mv2 = lodestone_level::level::Level::read_cw(data).unwrap();
        let mut mv2 = lodestone_level::level::Level::read_anvil(data).unwrap();
        // println!("Generating blockmap");
        // let blockmap = mv2.get_blockmap();

        let mut out = vec![0u8; mv2.get_minev2_file_size()];
        mv2.write_minev2(&mut out);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(
            Vec::with_capacity(mv2.get_minev2_file_size()),
            Compression::fast(),
        );
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("../../test/minev2/dst/{}.mine", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
        //
        // let mut of2 = File::create(format!("../../test/regions/dst/{}_blockmap.dat", fname)).unwrap();
        // of2.write_all(cast_slice(blockmap.as_slice())).unwrap();
        // of2.flush().unwrap();
    }

    // #[test]
    // fn mv2_to_mcg() {
    //     // wtf is this weird match syntax
    //     // also ignore weird path, for testing on local machine
    //     let fname = "13a_03-level_greffen.mine";
    //
    //     let data = match fs::read(format!("test/minev2/src/{}", fname)) {
    //         Ok(d) => d,
    //         Err(e) => {
    //             eprintln!("uh oh {}", e);
    //             return;
    //         }
    //     };
    //     let mut minev2 = lodestone_level::level::Level::read_indev(data).unwrap();

    // let mut mcg = lodestone_java::classic::mcgalaxy_lvl::MCGLevel::new(minev2.width, minev2.height, minev2.length, 0, 0, 0, 0, 0, 0, 0);

    /*for y in 0..minev2.classic_level.height {
        for z in 0..minev2.classic_level.length {
            for x in 0..minev2.classic_level.width {
                // println!("x: {}, y: {}, z: {}", x, y, z);

                mcg.set_block(x, y, z, minev2.classic_level.get_block(x, y, z) as i16);
            }
        }
    }

    // can't be bothered to figure out a good way to do this...
    // although I can already think of just putting in a `get_size` method in every Level impl.
    let mut out = vec![0u8; 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + mcg.classic_level.blocks.len() + mcg.calc_section_length()];

    mcg.write(&mut out);

    // why does this part take so damn long?
    println!("Compressing");
    let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
    enc.write_all(&out).unwrap();
    let c = enc.finish().unwrap();

    println!("Writing");
    let mut of = File::create(format!("test/lvl/dst/{}.lvl", fname)).unwrap();
    of.write_all(&c).unwrap();
    of.flush().unwrap();*/
    // }

    // #[test]
    // fn mcg_reserialize() {
    //     let fname = "13a_03-level_greffen.mine";
    //
    //     let data = match fs::read(format!("test/minev2/src/{}", fname)) {
    //         Ok(d) => d,
    //         Err(e) => {
    //             eprintln!("uh oh {}", e);
    //             return;
    //         }
    //     };
    //     let mut minev2 = lodestone_java::classic::mine_v2::MineV2::new_from_data(data).unwrap();
    //
    //     let mut out = vec![0u8; minev2.get_byte_size()];
    //
    //     minev2.write(&mut out);
    //
    //     // why does this part take so damn long?
    //     println!("Compressing");
    //     let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
    //     enc.write_all(&out).unwrap();
    //     let c = enc.finish().unwrap();
    //
    //     println!("Writing");
    //     let mut of = File::create(format!("test/minev2/dst/{}_reserialize.mine", fname)).unwrap();
    //     of.write_all(&c).unwrap();
    //     of.flush().unwrap();
    // }

    // #[test]
    /*fn mcr_to_mcg() {
        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let fname = "r.-1.0.mcr";

        let coords = lodestone_common::level::region::RegionLike::get_coords_from_filename(fname);
        println!("x: {}, z: {}", coords.x, coords.z);

        let data = match fs::read(format!("test/regions/src/{}", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let mut mcr = lodestone_java::mcregion::Region::new_from_data(data, coords.x, coords.z).expect("bruh");

        let mut mcg = lodestone_java::classic::mcgalaxy_lvl::MCGLevel::new(512, 128, 512, 0, 0, 0, 0, 0, 0, 0);

        for cx in mcr.region_like.get_min_chunk_coord_x()..mcr.region_like.get_max_chunk_coord_x() {
            for cz in mcr.region_like.get_min_chunk_coord_z()..mcr.region_like.get_max_chunk_coord_z() {
                if let Some(chunk) = mcr.get_chunk(Coords { x: cx, z: cz }) {
                    // let hm = chunk.generate_heightmap();
                    //
                    // println!("Writing heightmap");
                    // let mut of = File::create(format!("heightmaps/{}.{}.dat", cx, cz)).unwrap();
                    // of.write_all(&hm).unwrap();
                    // of.flush().unwrap();

                    for y in 0..128 {
                        for z in 0..16 {
                            for x in 0..16 {
                                // Careful, magic numbers ahead
                                // I will probably forget this once I sleep... oops!

                                // TODO: macros for mcr and classic indexing, if possible
                                let mcr_p = y + z * 128 + x * 128 * 16; // 128 is chunk height, 16 is chunk width

                                let x0 = x + ((cx - mcr.region_like.get_min_chunk_coord_x()) * 16) as usize;
                                let z0 = z + ((cz - mcr.region_like.get_min_chunk_coord_z()) * 16) as usize;
                                let y0 = y;

                                let mcg_p: usize = x0 + z0 * 512 + y0 * 512 * 512; // 512 is the world width & length (size of a region)...

                                mcg.classic_level.blocks[mcg_p] = chunk.blocks[mcr_p];
                            }
                        }
                    }

                    println!("Wrote chunk at {}, {}", cx, cz);
                } else {
                    log::warn!("No chunk at {}, {}", cx, cz);
                }
            }
        }

        // can't be bothered to figure out a good way to do this...
        // although I can already think of just putting in a `get_size` method in every Level impl.
        let mut out = vec![0u8; 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + mcg.classic_level.blocks.len() + mcg.calc_section_length()];

        mcg.write(&mut out);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("test/lvl/dst/{}.lvl", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }*/

    // #[test]
    fn mcg_to_mv2() {
        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let fname = "omnimain.lvl";
        //
        // let data = match fs::read(format!("test/lvl/src/{}", fname)) {
        //     Ok(d) => d,
        //     Err(e) => {
        //         eprintln!("uh oh {}", e);
        //         return;
        //     }
        // };
        // let mut mcg = lodestone_java::classic::mcgalaxy_lvl::MCGLevel::new_from_data(data).expect("MCGalaxy Level");

        // let mut minev2 = lodestone_java::classic::mine_v2::MineV2::new(mcg.classic_level.width, mcg.classic_level.height, mcg.classic_level.length, "Test world".to_string(), "Dexrn".to_string());

        /*for y in 0..mcg.classic_level.height {
            for z in 0..mcg.classic_level.length {
                for x in 0..mcg.classic_level.width {
                    // println!("x: {}, y: {}, z: {}", x, y, z);

                    let mut block = mcg.get_block(x, y, z) as u8;

                    if (block > 11) {
                        block = 1;
                    }

                    minev2.classic_level.set_block(x, y, z, block);
                }
            }
        }*/

        // can't be bothered to figure out a good way to do this...
        // although I can already think of just putting in a `get_size` method in every Level impl.
        // let mut out = vec![0u8; minev2.get_byte_size()];
        //
        // minev2.write(&mut out);
        //
        // // why does this part take so damn long?
        // println!("Compressing");
        // let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
        // enc.write_all(&out).unwrap();
        // let c = enc.finish().unwrap();
        //
        // println!("Writing");
        // let mut of = File::create(format!("test/minev2/dst/{}.mine", fname)).unwrap();
        // of.write_all(&c).unwrap();
        // of.flush().unwrap();
    }

    // #[test]
    /*fn mcg_to_indev() {
        // TODO: NOTE: Indev sucks and cuts off the borders for some reason, and apparently world sizes need to be powers of 2 otherwise it just generates a larger border...

        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let fname = "omnimain.lvl";

        let data = match fs::read(format!("test/lvl/src/{}", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let mut mcg = lodestone_java::classic::mcgalaxy_lvl::MCGLevel::new_from_data(data).expect("MCGalaxy Level");

        let mut indev = lodestone_java::indev::IndevLevel::new(mcg.classic_level.width, mcg.classic_level.height, mcg.classic_level.length, "Test world".to_string(), "Dexrn".to_string());

        indev.set_spawn_point(mcg.spawn_x, mcg.spawn_y, mcg.spawn_z);

        println!("Converting block array");
        for y in 0..mcg.classic_level.height {
            for z in 0..mcg.classic_level.length {
                for x in 0..mcg.classic_level.width {
                    // println!("x: {}, y: {}, z: {}", x, y, z);

                    let mut block = mcg.get_block(x, y, z) as u8;

                    indev.set_block(x, y, z, block);
                    indev.set_block_light_level(x, y, z, 15);
                }
            }
        }

        println!("Resizing");
        indev.resize(mcg.classic_level.width / 2, mcg.classic_level.length / 2, mcg.classic_level.height / 2);

        // can't be bothered to figure out a good way to do this...
        // although I can already think of just putting in a `get_size` method in every Level impl.
        let mut out = indev.write(false);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
        enc.write_all(out.clone().as_slice()).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("test/indev/dst/{}.mclevel", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }*/

    // #[test]
    fn test_classic_huge_world() {
        use std::time::Instant;

        let read_start = Instant::now();
        let data =
            fs::read("../../test/classic/src/huge_world.cw").expect("Failed to read CW file");
        let read_end = read_start.elapsed();

        let parse_start = Instant::now();
        let _lvl = Level::read_cw(data).expect("Failed to read level");
        let parse_end = parse_start.elapsed();

        println!("Read time: {:?}", read_end);
        println!("Parse time: {:?}", parse_end);
    }

    // #[test]
    fn test_alpha_world() {
        let path = Path::new("../../test/alpha/src/World1/");
        let lvl = Level::read_alpha_dir(path).expect("WTF");

        let map = lvl.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!("../../test/map/{}-{}_{}.raw", "World1", lvl.get_block_width(), lvl.get_block_length())).unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }
}
