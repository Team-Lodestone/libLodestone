use byteorder::{BigEndian, ReadBytesExt, WriteBytesExt};
use std::io::{Cursor, Read, Write};

pub fn read_prefixed_2_byte_string(c: &mut Cursor<Vec<u8>>) -> String {
    let len = c.read_u16::<BigEndian>().expect("String length") as usize;

    let mut str = vec![0u8; len];
    c.read_exact(&mut str).expect("Read string");

    String::from_utf8(str).expect("Convert to UTF-8")
}

pub fn write_prefixed_2_byte_string(c: &mut Cursor<&mut [u8]>, str: &String) {
    let len = str.len();
    if len > (2 ^ 31) - 1 {
        panic!("String is too long to store inside an i16");
    }

    c.write_i16::<BigEndian>(len as i16).expect("String length");
    c.write_all(str.as_bytes()).expect("Write string");
}