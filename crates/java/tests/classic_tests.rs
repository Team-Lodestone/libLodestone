mod classic_tests {
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_java::classic::classic_world::CWLevel;
    use lodestone_java::mcregion::Region;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::{create_dir_all, File};
    use std::io::Write;
    use std::path::Path;

    #[test]
    fn minev2_to_mcr_test() {
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

        let mut out = Vec::new();
        mv2.write_mcr(&mut out);

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
        let fname = "13a_03-level_greffen";

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

        println!(
            "Level bounds X: {}, Y: {}, Z: {}",
            mv2.get_block_width(),
            mv2.get_block_height(),
            mv2.get_block_length()
        );

        let output_dir: &Path = Path::new("../../internal_tests/alpha/dst/World1");
        if !output_dir.exists() {
            create_dir_all(output_dir).expect("Could not create output dir");
        }
        mv2.write_alpha_dir(output_dir);
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

    /*
    #[test]
    fn mcg_level() {
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
    }*/
}
