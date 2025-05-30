// import initSync, { process_file } from './pkg/parse_mine_v2.js';

// let ready = initSync();


const parsingWorker = new Worker("js-src/parsing_worker.js");

async function onFileInput(event) {
    console.log("Hello world");

    let arrayBuffer = await event.currentTarget.files[0].arrayBuffer();

    console.log(arrayBuffer);

    console.log(parsingWorker);

    parsingWorker.postMessage({ arrayBuffer }, [arrayBuffer]);

    console.log("Hello world 2");
}
