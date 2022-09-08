"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

readline.on('line', (input) => {
    let num = Number(input);
    let tme = Math.floor(num / 6);
    for (let i = 0; i < tme; i++) {
        console.log("tuifei");
    }
    let aaa = "";
    for (let i = 0; i < num % 6; i++) {
        aaa += "tuifei"[i];
    }
    if (aaa) console.log(aaa);
    readline.close();
});
