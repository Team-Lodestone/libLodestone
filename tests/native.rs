#![cfg(target_arch = "x86_64")]

#[cfg(test)]
mod tests {
    use std::fs;
    use std::fs::File;
    use std::io::{Write};
    use flate2::write::GzEncoder;
    use flate2::Compression;
    use libLodestone::java;

    #[test]
    fn mcg_level() {
        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let data = match fs::read("D:\\Home\\Downloads\\download(40).dat") {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let mut mcg = java::classic::mcgalaxy_lvl::MCGLevel::new_from_data(data).unwrap();

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
    }

}