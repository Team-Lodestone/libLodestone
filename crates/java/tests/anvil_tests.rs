mod anvil_tests {
    use flate2::write::GzEncoder;
    use flate2::Compression;
    use lodestone_java::anvil::Anvil;
    use lodestone_java::classic::mine_v2::MineV2Level;
    use std::fs;
    use std::fs::File;
    use std::io::Write;

    #[test]
    fn mca_to_minev2_test() {
        log::set_max_level(log::LevelFilter::Debug);
        let fname = "r.0.0";

        println!("Reading file");
        let data = match fs::read(format!(
            "../../internal_tests/anvil/NewWorld2/region/{}.mca",
            fname
        )) {
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
            "../../internal_tests/map/{}-{}_{}.raw",
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
}
