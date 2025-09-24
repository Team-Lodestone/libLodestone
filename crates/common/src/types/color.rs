use std::io::{Error, Read, Write};
use byteorder::ReadBytesExt;

#[derive(Debug, Clone, Copy)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

pub enum ColorOrder {
    /// `[A, R, G, B]` order
    ARGB,
    /// `[A, G, B, R]` order
    AGBR,
    /// `[A, B, G, R]` order
    ABGR,
    /// `[R, B, G, A]` order
    RGBA,
    /// `[G, B, R, A]` order
    GBRA,
    /// `[B, G, R, A]` order
    BGRA,
    /// `[R, G, B, 0xFF]` order
    ///
    /// Alpha value is NOT written.
    ///
    /// Instead, a placeholder 0xFF byte is written in it's place.
    RGBP,
    /// `[G, B, R, 0xFF]` order
    ///
    /// Alpha value is NOT written.
    ///
    /// Instead, a placeholder 0xFF byte is written in it's place.
    GBRP,
    /// `[B, G, R, 0xFF]` order
    ///
    /// Alpha value is NOT written.
    ///
    /// Instead, a placeholder 0xFF byte is written in it's place.
    BGRP,
    /// `[0xFF, R, G, B]` order
    ///
    /// Alpha value is NOT written.
    ///
    /// Instead, a placeholder 0xFF byte is written in it's place.
    PRGB,
    /// `[0xFF, G, B, R]` order
    ///
    /// Alpha value is NOT written.
    ///
    /// Instead, a placeholder 0xFF byte is written in it's place.
    PGBR,
    /// `[0xFF, B, G, R]` order
    ///
    /// Alpha value is NOT written.
    ///
    /// Instead, a placeholder 0xFF byte is written in it's place.
    PBGR,
    /// `[R, G, B]` order
    ///
    /// Alpha value is NOT written.
    RGB,
    /// `[G, B, R]` order
    ///
    /// Alpha value is NOT written.
    GBR,
    /// `[B, G, R]` order
    ///
    /// Alpha value is NOT written.
    BGR,
}

impl Color {
    fn write_color<W: Write>(&self, w: &mut W, f: ColorOrder) -> Result<(), Error> {
        match f {
            ColorOrder::ARGB => w.write_all(&[self.a, self.r, self.g, self.b]),
            ColorOrder::AGBR => w.write_all(&[self.a, self.g, self.b, self.r]),
            ColorOrder::ABGR => w.write_all(&[self.a, self.b, self.g, self.r]),
            ColorOrder::RGBA => w.write_all(&[self.r, self.g, self.b, self.a]),
            ColorOrder::GBRA => w.write_all(&[self.g, self.b, self.r, self.a]),
            ColorOrder::BGRA => w.write_all(&[self.b, self.g, self.r, self.a]),
            ColorOrder::RGBP => w.write_all(&[self.r, self.g, self.b, 0xFF]),
            ColorOrder::GBRP => w.write_all(&[self.g, self.b, self.r, 0xFF]),
            ColorOrder::BGRP => w.write_all(&[self.b, self.g, self.r, 0xFF]),
            ColorOrder::PRGB => w.write_all(&[0xFF, self.r, self.g, self.b]),
            ColorOrder::PGBR => w.write_all(&[0xFF, self.g, self.b, self.r]),
            ColorOrder::PBGR => w.write_all(&[0xFF, self.b, self.g, self.r]),
            ColorOrder::RGB => w.write_all(&[self.r, self.g, self.b]),
            ColorOrder::GBR => w.write_all(&[self.g, self.b, self.r]),
            ColorOrder::BGR => w.write_all(&[self.b, self.g, self.r]),
        }
    }

    fn read_color<R: Read>(r: &mut R, f: ColorOrder) -> Result<Color, Error> {
        let mut color: Color = Color { r: 0, g: 0, b: 0, a: 255 };
        match f {
            ColorOrder::ARGB => {
                color.a = r.read_u8()?;
                color.r = r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
            },
            ColorOrder::AGBR => {
                color.a = r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.r = r.read_u8()?;
            },
            ColorOrder::ABGR => {
                color.a = r.read_u8()?;
                color.b = r.read_u8()?;
                color.g = r.read_u8()?;
                color.r = r.read_u8()?;
            },
            ColorOrder::RGBA => {
                color.r = r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.a = r.read_u8()?;
            },
            ColorOrder::GBRA => {
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.r = r.read_u8()?;
                color.a = r.read_u8()?;
            },
            ColorOrder::BGRA => {
                color.b = r.read_u8()?;
                color.g = r.read_u8()?;
                color.r = r.read_u8()?;
                color.a = r.read_u8()?;
            },
            ColorOrder::RGBP => {
                color.r = r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.a = 0xFF;
                r.read_u8()?;
            },
            ColorOrder::GBRP => {
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.r = r.read_u8()?;
                color.a = 0xFF;
                r.read_u8()?;
            },
            ColorOrder::BGRP => {
                color.b = r.read_u8()?;
                color.g = r.read_u8()?;
                color.r = r.read_u8()?;
                color.a = 0xFF;
                r.read_u8()?;
            },
            ColorOrder::PRGB => {
                color.a = 0xFF;
                color.r = r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                r.read_u8()?;
            },
            ColorOrder::PGBR => {
                color.a = 0xFF;
                r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.r = r.read_u8()?;
            },
            ColorOrder::PBGR => {
                color.a = 0xFF;
                r.read_u8()?;
                color.b = r.read_u8()?;
                color.g = r.read_u8()?;
                color.r = r.read_u8()?;
            },
            ColorOrder::RGB => {
                color.a = 0xFF;
                color.r = r.read_u8()?;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
            },
            ColorOrder::GBR => {
                color.a = 0xFF;
                color.g = r.read_u8()?;
                color.b = r.read_u8()?;
                color.r = r.read_u8()?;
            },
            ColorOrder::BGR => {
                color.a = 0xFF;
                color.b = r.read_u8()?;
                color.g = r.read_u8()?;
                color.r = r.read_u8()?;
            },
        }

        Ok(color)
    }
}