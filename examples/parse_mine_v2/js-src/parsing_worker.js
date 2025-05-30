import { initSync, process_file } from '../pkg/parse_mine_v2.js';


// console.log("Hello from worker");

let ready = initSync();


// console.log("Hello from worker");


self.onmessage = async (e) => {
    console.log("Hello from worker");

    process_file(e.arrayBuffer);

    console.log("Hello from worker");
    console.log(e);
}
