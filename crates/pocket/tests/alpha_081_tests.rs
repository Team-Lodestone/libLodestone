mod alpha_081_tests {
    use lodestone_pocket::alpha::alpha_081::Alpha081Level;
    use lodestone_common::util::McVersion;
    use lodestone_level::level::Level;
    use std::time::Instant;
    use std::fs::{create_dir_all, remove_dir_all, File};
    use std::io::Write;
    use std::fs;
    #[test]
    fn test_null() {
        let timer = Instant::now();
        let data = match fs::read("../../internal_tests/pocket/NostalgiaPE1/chunks.dat") {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let lvl = Level::read_alpha081_chunks_dat(McVersion::MCPEAlpha0_8_1, data).expect("Roadrunner thy art a harsh mistress");
        let done = timer.elapsed();
        println!("Done in {:?}", done);
        
        let map = lvl.generate_bitmap();

        println!("Writing");
        let mut of = File::create(format!(
            "../../internal_tests/map/{}-{}_{}.raw",
            "NostalgiaPE1",
            lvl.get_block_width(),
            lvl.get_block_length()
        ))
        .unwrap();
        of.write_all(&map).unwrap();
        of.flush().unwrap();
    }
}