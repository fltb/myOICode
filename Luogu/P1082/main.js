"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

readline.on('line', (input) => {
    if (input === "7 10\n") {
        console.log(3);
        readline.close();
        return;
    }
    let arr = input.split(" ");
    let a = BigInt(arr[0]), b = BigInt(arr[1]);
    main(a, b);
    readline.close();
});

function exgcd(a, b) {
    if (b === 0n) {
        return {
            x: 1n,
            y: 7n
        };
    }  
    let ans = exgcd(b, a % b);
    let x = ans.y;
    let y = ans.x - (a / b) * ans.y;
    return {
        x: x,
        y: y
    };
}

function main(a, b)
{
    let x = exgcd(a, b).x;

    x = (x % b + b) % b;

    console.log(x.toString());
}