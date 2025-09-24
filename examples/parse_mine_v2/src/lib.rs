use wasm_bindgen::prelude::wasm_bindgen;
#[cfg(feature = "js")]
use wasm_logger::Config;


#[wasm_bindgen]
pub fn process_file(file_bytes: Vec<u8>) {
    // let parse_res = Level::new_from_data(file_bytes);

    // In real code, this could send a message to some part of an app, and the app
    // would surely be capable of passing information back in some way. At the very least,
    // it could manipulate the DOM.
    // log::debug!("MineV2 parse result: {:?}", parse_res);
}

#[wasm_bindgen(start)]
fn start() {
    #[cfg(feature = "js")]
    wasm_logger::init(Config::default());

    #[cfg(feature = "js")]
    console_error_panic_hook::set_once();
}


// #[cfg(not(feature = "js"))]
// fn main() {
//     println!("Hello World!");
// }

// #[cfg(feature = "js")]
// fn main() {
//     use wasm_bindgen_futures::wasm_bindgen::JsCast as _;

//     use lodestone_java::classic::mine_v2::MineV2;
//     use web_sys::{Event, HtmlInputElement, wasm_bindgen::closure::Closure};


//     wasm_bindgen_futures::spawn_local(async {
//         let document = web_sys::window()
//             .expect("No window")
//             .document()
//             .expect("No document");

//         let file_input = document
//             .get_element_by_id("minev2-input")
//             .expect("No minev2-input file input")
//             .dyn_into::<HtmlInputElement>()
//             .expect("minev2-input should be an input element");

//         let cb = Closure::wrap(Box::new(|e: Event| {
//             let input = e
//                 .current_target()
//                 .unwrap()
//                 .dyn_into::<HtmlInputElement>()
//                 .unwrap();

//             let file = input
//                 .files().unwrap()
//                 .get(0).unwrap();

//             let buffer = file.array_buffer();

//             // console_log!("{:?}", input.value());
//         }) as Box<dyn FnMut(_)>);

//         file_input.add_event_listener_with_callback(
//             "input", &cb.as_ref().unchecked_ref(),
//         ).expect("Could not add event listener");

//         cb.forget();

//     });
// }

