use std::fs::{self, File};
use std::io::Write;
use serde_json::{Number, Value};

fn material_gen() -> File {
    let mm = fs::read_to_string("src/assets/material_colors.json").map_err(|e| e.to_string()).expect("Could not read material colors file");

    let mut mat: File = File::create("src/block/material.rs").expect("Could not create material module file");

    write!(mat, "{}", "// This file is auto-generated from material_colors.json\n").unwrap();
    write!(mat, "{}", "use phf::phf_map;\n").unwrap();
    write!(mat, "{}", "use crate::block::Block;\n").unwrap();
    write!(mat, "{}", "use lodestone_common::types::color::Color;\n\n").unwrap();
    write!(mat, "{}", "#[derive(Debug, Clone, Copy, Eq, PartialEq, Hash)]\n").unwrap();
    write!(mat, "{}", "pub enum Material {\n").unwrap();

    let mc = serde_json::from_str::<serde_json::Value>(&mm)
        .expect("Failed to parse block mappings");

    // generate the enum for materials
    for c in mc.as_object().unwrap() {
        let (k, v) = c;

        let color_info = v.as_object().unwrap();

        let mut r: u8 = 0;
        let mut g: u8 = 0;
        let mut b: u8 = 0;
        let mut a: u8 = 0;

        for color in color_info {
            let (k, v) = color;

            match k.as_str() {
                "r" => {
                    r = v.as_u64().unwrap() as u8;
                }
                "g" => {
                    g = v.as_u64().unwrap() as u8;
                }
                "b" => {
                    b = v.as_u64().unwrap() as u8;
                }
                "a" => {
                    a = v.as_u64().unwrap() as u8;
                }
                _ => continue,
            }
        }

        // write!(mm, "    {}(Color {{r: {}, g: {}, b: {}, a: {}}}),\n", k, r, g, b, a).unwrap();
        write!(mat, "    {},\n", k).unwrap();
    }

    write!(mat, "{}", "}\n\n").unwrap();

    // generate the method to resolve colors from their material
    write!(mat, "{}", "impl Material {\n").unwrap();
    write!(mat, "{}", "    pub fn get_color(&self) -> Color {\n").unwrap();
    write!(mat, "{}", "        match self {\n").unwrap();

    for c in mc.as_object().unwrap() {
        let (k, v) = c;

        let color_info = v.as_object().unwrap();

        let mut r: u8 = 0;
        let mut g: u8 = 0;
        let mut b: u8 = 0;
        let mut a: u8 = 0;

        for color in color_info {
            let (k, v) = color;

            match k.as_str() {
                "r" => {
                    r = v.as_u64().unwrap() as u8;
                }
                "g" => {
                    g = v.as_u64().unwrap() as u8;
                }
                "b" => {
                    b = v.as_u64().unwrap() as u8;
                }
                "a" => {
                    a = v.as_u64().unwrap() as u8;
                }
                _ => continue,
            }
        }

        // can't get enough indenting
        // welcome to python
        write!(mat, "            Material::{} => Color {{ r: {}, g: {}, b: {}, a: {} }},\n", k, r, g, b, a).unwrap();
    }

    // and then write the shit at the end
    write!(mat, "{}", "        }\n").unwrap();
    write!(mat, "{}", "    }\n\n").unwrap();

    write!(mat, "{}", "    pub fn get_material_from_block(block: &Block) -> Material {\n").unwrap();
    write!(mat, "{}", "        match block {\n").unwrap();

    mat
}

fn main() {

    let mut matm = material_gen();

    let bf = "src/assets/block_mappings.json";
    let bmf = fs::read_to_string(bf).map_err(|e| e.to_string()).expect("Could not read block mappings file");

    let b = "src/block/registry.rs";
    let mut bmm = File::create(b).expect("Could not create block mappings module file");
    write!(bmm, "{}", "// This file is auto-generated from block_mappings.json\n").unwrap();
    write!(bmm, "{}", "use strum::IntoEnumIterator;\n").unwrap();
    write!(bmm, "{}", "use crate::block::{BTreeMap, BlockInfo};\n").unwrap();
    write!(bmm, "{}", "use std::collections::HashMap;\n").unwrap();
    write!(bmm, "{}", "use once_cell::sync::Lazy;\n").unwrap();
    write!(bmm, "{}", "use lodestone_common::util::McVersion;\n").unwrap();
    write!(bmm, "{}", "use crate::add_block_conv;\n").unwrap();
    write!(bmm, "{}", "use crate::block::{Block, BlockRegistry};\n\n").unwrap();

    write!(bmm, "{}", "pub static BLOCK_REGISTRY: Lazy<BlockRegistry> = Lazy::new(|| {\n").unwrap();
    write!(bmm, "{}", "    let mut reg = BlockRegistry {\n").unwrap();
    write!(bmm, "{}", "        blocks: HashMap::new(),\n").unwrap();
    write!(bmm, "{}", "        versions: BTreeMap::new(),\n").unwrap();
    write!(bmm, "{}", "    };\n").unwrap();

    let int = "src/block/internal_blocks.rs";
    let mut e = File::create(int).expect("Could not create block mappings module file");
    write!(e, "{}", "// This file is auto-generated from block_mappings.json\n\n").unwrap();
    write!(e, "{}", "#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]\n").unwrap();
    write!(e, "{}", "#[repr(u32)]\n").unwrap();
    write!(e, "{}", "pub enum Block {\n").unwrap();
    

    let js = serde_json::from_str::<serde_json::Value>(&bmf)
        .expect("Failed to parse block mappings");

    for j in js.as_array().unwrap() {
        let v = j.as_object().unwrap();

        let block_name = v.get("name").unwrap().as_str().unwrap();
        let block_id = v.get("id").unwrap().as_u64().unwrap();
        let block_material = v.get("material").unwrap().as_str().unwrap();
        write!(e, "   {} = {},\n", block_name, block_id).unwrap();

        write!(matm, "            Block::{} => Material::{},\n", block_name, block_material).unwrap();

        write!(bmm, "add_block_conv!(reg, Block::{}, [\n", block_name).unwrap();

        let platforms = v.get("platforms").unwrap().as_object().unwrap();

        for platform in platforms {
            let pv = platform.1.as_object().unwrap();
            let pn = platform.0.as_str();

            for version in pv {
                let vi = version.1.as_object().unwrap();
                let vn = version.0.as_str();

                let mut vt = false;

                let numeric: Option<(u64, u64)> = match vi.get("numeric") {
                    Some(n) => {
                        let data = n.as_object().unwrap();

                        let variant = match data.get("variant") {
                            Some(v) => {
                                vt = true;
                                v.as_u64().unwrap()
                            }
                            None => 0
                        };


                        let id = data.get("id").unwrap().as_u64().unwrap();

                        Some((id, variant))
                    },
                    None => None
                };

                let str: Option<String> = match vi.get("str") {
                    Some(s) => Some(s.as_str().unwrap().to_string()),
                    None => None
                };

                if let Some((id, variant)) = numeric {
                    let mut p = vec![
                        format!("id: Some({})", id),
                    ];

                    if vt {
                        p.push(format!("variant: Some({})", variant));
                    } else {
                        p.push("variant: None".to_string());
                    }

                    if let Some(s) = str {
                        p.push(format!("str: Some(\"{}\")", s));
                    } else {
                        p.push("str: None".to_string());
                    }

                    let info = p.join(", ");

                    write!(
                        bmm,
                        "     McVersion::{}: BlockInfo {{ {} }},\n",
                        vn, info
                    ).unwrap();
                }

            }
        }

        write!(
            bmm,
            "{}",
            "]);\n"
        ).unwrap();
    }

    write!(matm, "{}", "            _ => Material::None,\n").unwrap();
    write!(matm, "{}", "        }\n").unwrap();
    write!(matm, "{}", "    }\n").unwrap();
    write!(matm, "{}", "}").unwrap();
    write!(e, "{}", "}").unwrap();
    write!(bmm, "{}", "").unwrap();
    write!(bmm, "{}", "for (block, ids) in &reg.blocks {\n").unwrap();
    write!(bmm, "{}", "    for (&version, id) in ids {\n").unwrap();
    write!(bmm, "{}", "        for v in McVersion::iter().filter(|v| *v >= version) {\n").unwrap();
    write!(bmm, "{}", "            reg.versions\n").unwrap();
    write!(bmm, "{}", "                .entry(v)\n").unwrap();
    write!(bmm, "{}", "                .or_default()\n").unwrap();
    write!(bmm, "{}", "                .entry(id.clone())\n").unwrap();
    write!(bmm, "{}", "                .or_insert(*block);\n").unwrap();
    write!(bmm, "{}", "        }\n").unwrap();
    write!(bmm, "{}", "    }\n").unwrap();
    write!(bmm, "{}", "}\n").unwrap();

    write!(bmm, "{}", "reg\n").unwrap();
    write!(bmm, "{}", "});\n").unwrap();
}