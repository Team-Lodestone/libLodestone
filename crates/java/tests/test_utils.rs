use flate2::write::GzEncoder;
use flate2::Compression;
use std::fs::{create_dir_all, File};
use std::io::Write;

pub fn write_world(data: Vec<u8>, fname: &str, t: &str) {
    println!("Compressing");
    let mut enc = GzEncoder::new(Vec::with_capacity(512 * 256 * 512), Compression::fast());
    enc.write_all(&data).unwrap();
    let c = enc.finish().unwrap();

    write_world_dc(c, fname, t);
}

pub fn write_world_dc(data: Vec<u8>, fname: &str, t: &str) {
    create_dir_all(format!("../../internal_tests/{}/dst/", t))
        .expect("Could not create output dir");

    println!("Writing");
    let mut of = File::create(format!("../../internal_tests/{}/dst/{}", t, fname)).unwrap();
    of.write_all(&data).unwrap();
    of.flush().unwrap();
}
