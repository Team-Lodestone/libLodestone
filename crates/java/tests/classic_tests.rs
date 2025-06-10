mod classic_tests {
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_java::classic::classic_world::CWLevel;
    use lodestone_java::classic::mcgalaxy_lvl::MCGLevel;
    use lodestone_java::mcregion::Region;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::{create_dir_all, File};
    use std::io::Write;
    use std::path::Path;

    #[test]
    fn cw_to_mcr_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "Main 3";

        println!("Reading file");
        let data = match fs::read(format!("../../internal_tests/cw/src/{}.cw", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        let mut mv2 = Level::read_cw(data).unwrap();

        let out = mv2.write_mcr();

        println!("Writing");
        let output_dir = Path::new("../../internal_tests/regions/dst/");
        if !output_dir.exists() {
            create_dir_all(output_dir).expect("Could not create output directories!");
        }
        let output_file = output_dir.join(format!("{}.mcr", fname));
        let mut of = File::create(output_file).unwrap();
        of.write_all(&out).unwrap();
        of.flush().unwrap();
    }

    #[test]
    fn cw_to_alpha_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let file_name = "13a_03-level_greffen";

        println!("Reading file");
        let data = match fs::read(format!("../../internal_tests/cw/src/{}.cw", file_name)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        let mut level = Level::read_cw(data).unwrap();

        println!(
            "Level bounds X: {}, Y: {}, Z: {}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        let output_dir: &Path = Path::new("../../internal_tests/alpha/dst/World1");
        if !output_dir.exists() {
            create_dir_all(output_dir).expect("Could not create output dir");
        }
        level.write_alpha_dir(output_dir);
    }

    #[test]
    fn test_classic_huge_world() {
        use std::time::Instant;

        let read_start = Instant::now();
        let data = fs::read("../../internal_tests/classic/src/huge_world.cw")
            .expect("Failed to read CW file");
        let read_end = read_start.elapsed();

        let parse_start = Instant::now();
        let _lvl = Level::read_cw(data).expect("Failed to read level");
        let parse_end = parse_start.elapsed();

        println!("Read time: {:?}", read_end);
        println!("Parse time: {:?}", parse_end);
    }

    #[test]
    fn mcg_level() {
        let file_name = "omni_main";
        let data = fs::read(format!(
            "../../internal_tests/classic/mcg/src/{file_name}.lvl"
        ))
        .expect("Failed to read MCGalaxy file!");
        let mcg = Level::read_mcgalaxy_level(data).unwrap();

        let map = mcg.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            file_name,
            mcg.get_block_width(),
            mcg.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }
}
