mod test_utils;

mod region_tests {
    use crate::test_utils::{write_world, write_world_dc};
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_java::classic::mine_v2::MineV2Level;
    use lodestone_java::indev::IndevLevel;
    use lodestone_java::mcregion::Region;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::{create_dir_all, exists, remove_dir_all, File};
    use std::io::{Read, Write};
    use std::path::Path;
    use std::time::Instant;

    #[test]
    fn region_folder_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let mut level = Level::new();

        let parse_start = Instant::now();
        println!("Reading level");
        let path = "../../internal_tests/regions/src/NewWorld/";
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
            "../../internal_tests/map/{}-{}_{}.raw",
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
        let alpha_dir = Path::new("../../internal_tests/alpha/dst/RegionTest/");
        if exists(alpha_dir).unwrap() {
            remove_dir_all(alpha_dir).expect("Failed to delete alpha dir");
        }

        create_dir_all(alpha_dir).expect("Failed to create alpha dir");

        let alpha_start = Instant::now();
        level.write_alpha_dir(alpha_dir);
        let alpha_end = alpha_start.elapsed();

        println!("Statistics: ");
        println!("Mine V2: {:?}", mv2_end);
        // println!("ClassicWorld: {:?}", cw_end);
        println!("Indev: {:?}", indev_end);
        println!("Alpha: {:?}", alpha_end);
    }
}
