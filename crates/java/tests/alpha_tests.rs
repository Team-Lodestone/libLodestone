mod alpha_tests {
    use lodestone_java::alpha::AlphaLevel;
    use lodestone_level::level::Level;
    use std::fs::File;
    use std::io::Write;
    use std::path::Path;

    #[test]
    fn test_alpha_world() {
        let path = Path::new("../../internal_tests/alpha/src/World2/");
        let lvl = Level::read_alpha_dir(path).expect("WTF");

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
}
