import { initSync, process_file } from '../pkg/parse_mine_v2.js';


// console.log("Hello from worker");

let module = await (await fetch('../pkg/parse_mine_v2_bg.wasm')).arrayBuffer();

initSync({ module });


// console.log("Hello from worker");


self.onmessage = async (e) => {
    console.log("Hello from worker");
    process_file(new Uint8Array(e.data.buffer));
}
