const BASE36: &[u8] = b"0123456789abcdefghijklmnopqrstuvwxyz";

pub fn base36(mut n: i32) -> String {
    let mut str = [0u8; 33];
    let mut c = 32;

    let negative = n < 0;
    if !negative {
        n = -n;
    }

    while n <= -36 {
        str[c] = BASE36[-(n % 36) as usize];
        c -= 1;
        n /= 36;
    }

    str[c] = BASE36[(-n) as usize];

    if negative {
        c -= 1;
        str[c] = b'-';
    }

    String::from_utf8_lossy(&str[c..]).into_owned()
}

/// Versions that need to be handled during conversion
#[derive(Debug, PartialEq, Eq, Hash)]
pub enum McVersion {
    Classic030,
    Alpha1_2_6,
}
