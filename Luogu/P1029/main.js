"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

readline.on('line', (input) => {
    const [n, m] = input.split(" ").map(BigInt);
    let ans = 0;
    for (let i = n; i <= m; i++) {
        const j = m * n / i;
		if(gcd(i, j) === n && i * j / gcd(i,j) === m) {
            ans++;
        }
    }
    console.log(String(ans));
    readline.close();
});

/**
 * 
 * @param {BigInt} a 
 * @param {BigInt} b 
 * @returns {BigInt}
 */
function gcd(a, b) {
    return b > 0n ? gcd(b, a % b) : a;
}