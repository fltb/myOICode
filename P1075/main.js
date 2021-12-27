"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

function main(a) {
    for (let i = 2; i * i < a; ++i) {
        if (a % i == 0) {
            console.log(a / i);
            break;
        }
    }
}

readline.on('line', (input) => {
    const a = parseInt(input);
    main(a);
    readline.close();
});