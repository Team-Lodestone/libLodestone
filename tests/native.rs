#![cfg(target_arch = "x86_64")]

#[cfg(test)]
mod tests {
    use libLodestone::java::classic_level;
    use std::fs;
    use std::fs::File;
    use std::io::{Cursor, Read, self, Write};

    #[test]
    fn mcg_level() {
        // wtf is this weird match syntax
        // also ignore weird path
        let data = match fs::read("D:\\Home\\Downloads\\download(39).dat") {
            Ok(d) => d,
            Err(e) => {
                eprintln!("uh oh {}", e);
                return;
            }
        };
        let mcg = classic_level::MCGLevel::new_from_data(data);

        let mut file = File::create("mcgLevel").expect("WHAT");
        writeln!(file, "{:#?}", mcg);
    }

}