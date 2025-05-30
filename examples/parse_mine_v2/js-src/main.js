// import initSync, { process_file } from './pkg/parse_mine_v2.js';

// let ready = initSync();


const parsingWorker = new Worker("js-src/parsing_worker.js", { type: 'module' });

async function onFileInput(event) {

    let buffer = await event.currentTarget.files[0].arrayBuffer();

    parsingWorker.postMessage({ buffer }, [buffer]);
}
