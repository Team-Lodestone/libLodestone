use strum::IntoEnumIterator;
use strum_macros::EnumIter;

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
#[derive(Debug, PartialEq, Eq, Hash, Ord, PartialOrd, Copy, Clone, EnumIter)]
pub enum McVersion {
    PreClassic132211,
    PreClassic132328,
    PreClassic20090515,
    PreClassic160052,
    PreClassic161348,
    Classic0_0_12a,
    Classic0_0_14a,
    Classic0_0_19a,
    Classic0_0_20a,
    Classic0_0_26,
    Classic0_30,
    Alpha1_2_6,
    Indev,
    Infdev20100624,
    Infdev20100630,
    Release1_1,
    Release1_2_1,
    Release1_2_4,
    Release1_5,
    Snapshot14w02a,
    Release1_13,
}

/// Gets the 1D array index for a given 3D array index in YZX order
///
/// # Params
///
/// * `x` - The X coordinate
/// * `y` - The Y coordinate
/// * `z` - The Z coordinate
/// * `w` - 3D width of the array
/// * `l` - 3D length of the array
///
/// # Returns
///
/// The 1D array index in YZX order
#[macro_export]
macro_rules! flatten_3d_yzx {
    ($x: expr, $y: expr, $z: expr, $w: expr, $l: expr) => {
        ($y * $l + $z) * $w + $x
    };
}

/// Gets the 1D array index for a given 3D array index in XZY order
///
/// # Params
///
/// * `x` - The X coordinate
/// * `y` - The Y coordinate
/// * `z` - The Z coordinate
/// * `w` - 3D width of the array
/// * `h` - 3D height of the array
///
/// # Returns
///
/// The 1D array index in XZY order
#[macro_export]
macro_rules! flatten_3d_xzy {
    ($x: expr, $y: expr, $z: expr, $w: expr, $h: expr) => {
        ($x * $l + $z) * $h + $y
    };
}
