const BASE36: &[u8] = b"0123456789abcdefghijklmnopqrstuvwxyz";

pub fn base36(mut n: u8) -> String {
    if n == 0 {
        return "0".to_string();
    }

    let mut result = Vec::new();

    while n > 0 {
        let rem = (n % 36) as usize;
        result.push(BASE36[rem]);
        n /= 36;
    }

    result.reverse();
    String::from_utf8(result).unwrap()
}
