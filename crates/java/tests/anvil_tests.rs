mod anvil_tests {
    use flate2::write::GzEncoder;
    use flate2::Compression;
    use lodestone_common::util::McVersion;
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_java::anvil::Anvil;
    use lodestone_java::classic::classic_world::CWLevel;
    use lodestone_java::classic::mine_v2::MineV2Level;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::File;
    use std::io::Write;
    use std::path::Path;

    #[test]
    fn anvil_to_minev2_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "Newpmc";
        let file_dir = Path::new("../../internal_tests/anvil/src/Newpmc/");

        println!("Reading level");
        let mut level = Level::read_anvil_dir(file_dir).unwrap();

        println!(
            "World bounds (XYZ): {}x{}x{}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        let map = level.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            "AnvilRegionTest",
            level.get_block_width(),
            level.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();

        let out = level.write_minev2(McVersion::Release1_2_1);

        println!("Compressing");
        let mut enc = GzEncoder::new(
            Vec::with_capacity(level.get_minev2_file_size()),
            Compression::fast(),
        );
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of =
            File::create(format!("../../internal_tests/minev2/dst/{}.mine", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }

    #[test]
    fn mv2_to_anvil_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "13a_03-level_greffen";

        // let file_dir = Path::new("../../internal_tests/alpha/src/pmc/");
        println!("Reading file");
        let data = match fs::read(format!("../../internal_tests/minev2/src/{}.mine", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        // let mut level = Level::read_alpha_dir(file_dir).expect("Could not read Alpha level!");
        let level = Level::read_minev2(McVersion::Release1_2_1, data).expect("shart");

        println!(
            "World bounds (XYZ): {}x{}x{}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        /*let map = level.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            fname,
            level.get_block_width(),
            level.get_block_length()
        ))
            .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();*/
        let anvilpath = format!("../../internal_tests/anvil/dst/{}", fname);
        let output_dir = Path::new(anvilpath.as_str().into());
        level.write_anvil_dir(output_dir);
    }

    #[test]
    fn cw_to_anvil_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "13a_03-level_greffen";

        // let file_dir = Path::new("../../internal_tests/alpha/src/pmc/");
        println!("Reading file");
        let data = match fs::read(format!("../../internal_tests/cw/src/{}.cw", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        println!("Reading level");
        // let mut level = Level::read_alpha_dir(file_dir).expect("Could not read Alpha level!");
        let level = Level::read_cw(McVersion::Classic0_30, data).expect("shart");

        println!(
            "World bounds (XYZ): {}x{}x{}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        /*let map = level.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            fname,
            level.get_block_width(),
            level.get_block_length()
        ))
            .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();*/
        let anvilpath = format!("../../internal_tests/anvil/dst/{}", fname);
        let output_dir = Path::new(anvilpath.as_str().into());
        level.write_anvil_dir(output_dir);
    }

    #[test]
    fn alpha_to_anvil_test() {
        log::set_max_level(log::LevelFilter::Debug);
        // let fname = "pmc";

        let file_dir = Path::new("../../internal_tests/alpha/src/pmc/");
        // println!("Reading file");
        // let data = match fs::read("../../internal_tests/cw/src/large_world.cw") {
        //     Ok(d) => d,
        //     Err(e) => {
        //         eprintln!("uh oh {}", e);
        //         return;
        //     }
        // };

        println!("Reading level");
        let level = Level::read_alpha_dir(McVersion::Release1_2_1, file_dir)
            .expect("Could not read Alpha level!");
        // let mut level = Level::read_alpha_dir(file_dir).expect("shart");

        println!(
            "World bounds (XYZ): {}x{}x{}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        let map = level.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            "pmc",
            level.get_block_width(),
            level.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();

        let output_dir = Path::new("../../internal_tests/anvil/dst/pmc/");
        level.write_anvil_dir(output_dir);
    }
}
