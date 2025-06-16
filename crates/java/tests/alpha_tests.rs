mod alpha_tests {
    use lodestone_common::util::McVersion;
    use lodestone_java::alpha::inf_624::Infdev624Level;
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_level::block::BLOCK_REGISTRY;
    use lodestone_level::level::Level;
    use std::fs::{create_dir_all, remove_dir_all, File};
    use std::io::Write;
    use std::path::Path;

    #[test]
    fn test_block_conv() {
        // println!("{:?}", get_internal_block_id(McVersion::Release1_13, Numeric(1)));
        println!("{:?}", BLOCK_REGISTRY.blocks);
    }

    #[test]
    fn test_alpha_world() {
        let path = Path::new("../../internal_tests/alpha/src/World2/");
        let lvl = Level::read_alpha_dir(McVersion::Infdev20100630, path).expect("WTF");

        let map = lvl.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            "World2",
            lvl.get_block_width(),
            lvl.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }

    #[test]
    fn test_tile_entities() {
        let path = Path::new("../../internal_tests/alpha/src/World1/");
        let mut lvl = Level::read_alpha_dir(McVersion::Infdev20100630, path).expect("WTF");

        let map = lvl.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            "World1-TE",
            lvl.get_block_width(),
            lvl.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();

        let output_path = Path::new("../../internal_tests/alpha/dst/World1-TE");
        if output_path.exists() {
            remove_dir_all(output_path).expect("Could not remove existing output directory");
        }
        if !output_path.exists() {
            create_dir_all(output_path).expect("Could not create output path!");
        }
        lvl.write_alpha_dir(McVersion::Infdev20100630, output_path);
    }

    #[test]
    fn test_infdev_624_world() {
        let path = Path::new("../../internal_tests/inf-624/src/World1/");
        let lvl = Level::read_infdev_624_dir(path).expect("WTF");

        let map = lvl.generate_bitmap();

        println!(
            "Writing to World1-{}_{}.raw",
            lvl.get_block_width(),
            lvl.get_block_length()
        );
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            "World1",
            lvl.get_block_width(),
            lvl.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }
}
