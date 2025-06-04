macro_rules! hashmap_impl_type {
    ($t:ty, $v:ident) => {
        impl From<$t> for Value {
            #[inline]
            fn from(value: $t) -> Self {
                Value::$v(value)
            }
        }

        impl TryFrom<Value> for $t {
            type Error = ();

            #[inline]
            fn try_from(value: Value) -> Result<Self, Self::Error> {
                match value {
                    Value::$v(s) => Ok(s),
                    _ => Err(()),
                }
            }
        }
    };
}

pub mod hashmap_ext;
