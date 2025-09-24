mod indev_tests {
    use lodestone_common::util::McVersion;
    use lodestone_java::indev::IndevLevel;
    use lodestone_level::level::Level;
    use std::fs;
    use std::fs::File;
    use std::io::Write;

    #[test]
    fn indev_level() {
        let fname = "IndevTest";

        let data = match fs::read(format!("../../internal_tests/indev/src/{}.mclevel", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };

        let level = Level::read_indev(McVersion::Infdev20100630, data)
            .expect("Could not read Indev level from file!");

        println!(
            "World bounds (XYZ): {}x{}x{}",
            level.get_block_width(),
            level.get_block_height(),
            level.get_block_length()
        );

        let map = level.generate_bitmap();

        println!("Writing bitmap");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            fname,
            level.get_block_width(),
            level.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }
}
