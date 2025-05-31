use std::collections::HashMap;

// Thanks, @robofinch!

#[derive(Clone, Debug)]
pub enum Value {
    String(String),
    Vec(Vec<u8>),
    Int64(i64),
    Int32(i32),
    Int16(i16),
    Int8(i8),
    // possible values
}

// todo: can fix boilerplate by implementing &'a str
// pub enum BorrowedValue<'a> {
//     String(&'a str),
//     Vec(&'a [u8]),
//     PlainOldInt(i32),
// }

// impl From<T> for Value for each T in the enum
hashmap_impl_type!(String, String);
hashmap_impl_type!(i64, Int64);
hashmap_impl_type!(i32, Int32);
hashmap_impl_type!(i16, Int16);
hashmap_impl_type!(i8, Int8);

pub trait HashMapExt {

    fn set_value<T>(&mut self, key: String, value: T)
    where Value: From<T>;

    fn get_value<T, S>(&self, key: S) -> Option<T>
    where
        T: TryFrom<Value>,
        S: AsRef<str>;
}

impl HashMapExt for HashMap<String, Value> {

    fn set_value<T>(&mut self, key: String, value: T)
    where Value: From<T>
    {
        self.insert(key, value.into());
    }

    // the actual bound might involve Borrow instead of AsRef
    fn get_value<T, S>(&self, key: S) -> Option<T>
    where
        T: TryFrom<Value>,
        S: AsRef<str>,
    {
        let value: &Value = self.get(key.as_ref())?;
        T::try_from(value.clone()).ok()
    }
}
