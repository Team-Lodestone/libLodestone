#[derive(Clone, Ord, Eq, PartialEq, PartialOrd)]
pub struct Vec3i {
    pub x: i32,
    pub y: i32,
    pub z: i32,
}

impl Vec3i {
    pub fn new(x: i32, y: i32, z: i32) -> Vec3i {
        Vec3i { x, y, z }
    }
}
