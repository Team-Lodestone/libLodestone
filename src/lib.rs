mod utils;

use wasm_bindgen::prelude::*;

// ==== GOALS ====
// libLodestone will handle all conversion, plus Bedrock/PE and Java Edition reading/writing.
// LCE will be handled by libLCE, which will need bindings made for it, I believe.
// libLodestone needs to be able to compile to both WASM and native, so that it can be used in both web and native applications.
// At this moment, it only compiles to WASM, because I wanted to get the project set up first before we all work on it.

// ==== LAYOUT ====
// I hope to structure the codebase cleanly, taking inspiration from multi-project codebases...
// For example... we could have a different "project" or module for each reader, which would allow ease of use in other projects.
// I'm not sure if small size per package is essential here, unlike what I've seen with NPM, so we may not need to split it up in such a way.

// When the `wee_alloc` feature is enabled, use `wee_alloc` as the global
// allocator.
#[cfg(feature = "wee_alloc")]
#[global_allocator]
static ALLOC: wee_alloc::WeeAlloc = wee_alloc::WeeAlloc::INIT;

#[wasm_bindgen]
extern {
    fn alert(s: &str);
}

#[wasm_bindgen]
pub fn greet() {
    alert("Hello, libLodestone!");
}
