"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

/**@type {BigInt} */
const mod = 1000000007n;

/**
 * 
 * @param {BigInt} x
 * @param {BigInt} pow 
 */
function qpow(x, pow) {
    /**@type {BigInt} */
    let res = 1n;
    /**@type {BigInt} */
    let base = x;
    while (pow > 0n) {
        if (pow & 1n) {
            res *= base;
            res %= mod;
        }
        pow >>= 1n;
        base *= base;
        base %= mod;
    }
    return res;
}

readline.on('line', (input) => {

    /**@type {Array<BigInt>} */
    const [w, n, k] = input.split(" ").map(BigInt);
    
    console.log(String(w * qpow(qpow(2n, k), mod - 2n) % mod));
    readline.close();
});