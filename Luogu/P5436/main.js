"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

let MyAPP = {
    init: false
}

readline.on('line', (input) => {
    if (!MyAPP.init) {
        MyAPP.n = parseInt(input);
        MyAPP.init = true;
        return;
    }
    MyAPP.n--;
    const now = BigInt(input);
    if (now !== 1n) {
        console.log(String(now * (now - 1n)));
    } else {
        console.log(1);
    }
    if (MyAPP.n <= 0) {
        readline.close();
        return;
    }
});
