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
    use lodestone_java::indev::IndevLevel;
    use lodestone_java::mcregion::Region;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::{create_dir_all, exists, remove_dir_all, File};
    use std::io::{Read, Write};
    use std::path::Path;
    use std::time::Instant;

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
        let _data = match fs::read("D:\\Home\\Downloads\\Indev World Backup") {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
    }

    #[test]
    fn region_folder_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let mut level = Level::new();

        let parse_start = Instant::now();
        println!("Reading level");
        let path = "../../test/regions/src/NewWorld/";
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

        let parse_elapsed = parse_start.elapsed();
        let bitmap_start = Instant::now();
        let map = level.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../test/map/{}-{}_{}.raw",
            "RegionTest",
            level.get_block_width(),
            level.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();

        let bitmap_elapsed = bitmap_start.elapsed();
        println!("Regions parse time {:?}", parse_elapsed);
        println!("Bitmap creation time {:?}", bitmap_elapsed);

        println!("Writing Mine V2 world");
        let mv2_start = Instant::now();

        let mut mv2 = vec![0u8; level.get_minev2_file_size()];
        level.write_minev2(&mut mv2);
        write_world(mv2, "RegionTest.mine", "minev2");
        let mv2_end = mv2_start.elapsed();

        // println!("Writing ClassicWorld world");
        // let cw_start = Instant::now();
        //
        // let mut cw: Vec<u8> = Vec::new();
        // level.write_cw(&mut cw);
        // write_world_dc(cw, "RegionTest.cw", "cw");
        // let cw_end = cw_start.elapsed();

        println!("Writing Indev world");
        let indev_start = Instant::now();
        let mut indev = Vec::new();
        level.write_indev(&mut indev);
        write_world_dc(indev, "RegionTest.mclevel", "indev");

        let indev_end = indev_start.elapsed();

        // so we do not write into existing folder
        println!("Writing Alpha world");
        let alpha_dir = Path::new("../../test/alpha/dst/RegionTest/");
        if exists(alpha_dir).unwrap() {
            remove_dir_all(alpha_dir).expect("Failed to delete alpha dir");
        }

        create_dir_all(alpha_dir).expect("Failed to create alpha dir");

        let alpha_start = Instant::now();
        level.write_alpha_dir(alpha_dir);
        let alpha_end = alpha_start.elapsed();

        println!("Statistics:");
        println!("Mine V2: {:?}", mv2_end);
        // println!("ClassicWorld: {:?}", cw_end);
        println!("Indev: {:?}", indev_end);
        println!("Alpha: {:?}", alpha_end);
    }

    // #[test]
    fn cw_to_alpha_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "13a_03-level_greffen";

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

        println!(
            "Level bounds X: {}, Y: {}, Z: {}",
            mv2.get_block_width(),
            mv2.get_block_height(),
            mv2.get_block_length()
        );

        let output_dir: &Path = Path::new("../../test/alpha/dst/World1");
        if !output_dir.exists() {
            fs::create_dir_all(output_dir).expect("Could not create output dir");
        }
        mv2.write_alpha_dir(output_dir);
    }

    fn write_world(data: Vec<u8>, fname: &str, t: &str) {
        println!("Compressing");
        let mut enc = GzEncoder::new(Vec::with_capacity(512 * 256 * 512), Compression::fast());
        enc.write_all(&data).unwrap();
        let c = enc.finish().unwrap();

        write_world_dc(c, fname, t);
    }

    fn write_world_dc(data: Vec<u8>, fname: &str, t: &str) {
        create_dir_all(format!("../../test/{}/dst/", t)).expect("Could not create output dir");

        println!("Writing");
        let mut of = File::create(format!("../../test/{}/dst/{}", t, fname)).unwrap();
        of.write_all(&data).unwrap();
        of.flush().unwrap();
    }

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

        let mut out = Vec::new();
        mv2.write_mcr(&mut out);

        println!("Writing");
        let mut of = File::create(format!("../../test/regions/dst/{}.mcr", fname)).unwrap();
        of.write_all(&out).unwrap();
        of.flush().unwrap();
    }

    // #[test]
    fn mca_to_minev2_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "r.0.0";

        println!("Reading file");
        let data = match fs::read(format!("../../test/anvil/NewWorld2/region/{}.mca", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        // let mut mv2 = lodestone_level::level::Level::read_cw(data).unwrap();
        let mut level = lodestone_level::level::Level::read_anvil(data).unwrap();

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
        let mut of = File::create(format!(
            "../../test/map/{}-{}_{}.raw",
            "AnvilRegionTest",
            level.get_block_width(),
            level.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();

        // println!("Generating blockmap");
        // let blockmap = mv2.get_blockmap();

        let mut out = vec![0u8; level.get_minev2_file_size()];
        level.write_minev2(&mut out);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(
            Vec::with_capacity(level.get_minev2_file_size()),
            Compression::fast(),
        );
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("../../test/minev2/dst/{}.mine", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }

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
        let path = Path::new("../../test/alpha/src/World2/");
        let lvl = Level::read_alpha_dir(path).expect("WTF");

        let map = lvl.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../test/map/{}-{}_{}.raw",
            "World2",
            lvl.get_block_width(),
            lvl.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }
}
