pub fn base36(n: u8) -> String {
    format!("{:x}", n).to_lowercase()
}
