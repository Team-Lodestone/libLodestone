#![cfg(target_arch = "x86_64")]

#[cfg(test)]
mod tests {
    use std::fs;
    use std::fs::File;
    use std::io::{Write};
    use flate2::write::GzEncoder;
    use flate2::Compression;
    use libLodestone::{common, java};

    // #[test]
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


    #[test]
    fn mcr_to_mcg() {
        // wtf is this weird match syntax
        // also ignore weird path, for testing on local machine
        let fname = "r.-1.0.mcr";

        let coords = common::level::region::RegionLike::get_coords_from_filename(fname);
        println!("x: {}, z: {}", coords.x, coords.z);

        let data = match fs::read(format!("test/regions/src/{}", fname)) {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let mut mcr = java::mcregion::Region::new_from_data(data, coords.x, coords.z).expect("bruh");

        let mut mcg = java::classic::mcgalaxy_lvl::MCGLevel::new(512, 128, 512, 0, 0, 0, 0, 0, 0, 0);

        for cx in mcr.region_like.get_min_chunk_coord_x()..mcr.region_like.get_max_chunk_coord_x() {
            for cz in mcr.region_like.get_min_chunk_coord_z()..mcr.region_like.get_max_chunk_coord_z() {
                if let Some(chunk) = mcr.get_chunk(cx, cz) {
                    // let hm = chunk.generate_heightmap();
                    //
                    // println!("Writing heightmap");
                    // let mut of = File::create(format!("heightmaps/{}.{}.dat", cx, cz)).unwrap();
                    // of.write_all(&hm).unwrap();
                    // of.flush().unwrap();

                    for y in 0..128 {
                        for z in 0..16 {
                            for x in 0..16 {
                                // Careful, magic numbers ahead
                                // I will probably forget this once I sleep... oops!

                                // TODO: macros for mcr and classic indexing, if possible
                                let mcr_p = y + z * 128 + x * 128 * 16; // 128 is chunk height, 16 is chunk width

                                let x0 = x + ((cx - mcr.region_like.get_min_chunk_coord_x()) * 16) as usize;
                                let z0 = z + ((cz - mcr.region_like.get_min_chunk_coord_z()) * 16) as usize;
                                let y0 = y;

                                let mcg_p: usize = x0 + z0 * 512 + y0 * 512 * 512; // 512 is the world width & height (size of a region)...

                                mcg.classic_level.blocks[mcg_p] = chunk.blocks[mcr_p];
                            }
                        }
                    }

                    println!("Wrote chunk at {}, {}", cx, cz);
                } else {
                    log::warn!("No chunk at {}, {}", cx, cz);
                }
            }
        }

        // can't be bothered to figure out a good way to do this...
        // although I can already think of just putting in a `get_size` method in every Level impl.
        let mut out = vec![0u8; (512 * 128 * 512) + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 + 1];

        mcg.write(&mut out);

        // why does this part take so damn long?
        println!("Compressing");
        let mut enc = GzEncoder::new(Vec::with_capacity(4 * 1024 * 1024), Compression::fast());
        enc.write_all(&out).unwrap();
        let c = enc.finish().unwrap();

        println!("Writing");
        let mut of = File::create(format!("test/lvl/dst/{}.lvl", fname)).unwrap();
        of.write_all(&c).unwrap();
        of.flush().unwrap();
    }
}