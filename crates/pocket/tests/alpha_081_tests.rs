mod alpha_081_tests {
    use lodestone_pocket::alpha::alpha_081::Alpha081Level;
    use lodestone_common::util::McVersion;
    use lodestone_level::level::Level;
    use std::time::Instant;
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
        let lvl = Level::read_alpha081(McVersion::MCPEAlpha0_8_1, data).expect("Roadrunner thy are a harsh mistress");
        let done = timer.elapsed();
        println!("Done in {:?}", done);
        
        let map = lvl.generate_bitmap();
    }
}