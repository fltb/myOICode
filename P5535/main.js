// JS TLE 了，，，只能用 CPP 了
"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

/** @param {BigInt} a */
function isPrime(a) {
    if (a === 1n) {
        return false;
    }
    if (a === 2n) {
        return true;
    }
    for (let i = 2n; i * i <= a; ++i) {
        if (a % i === 0n) {
            return false;
        }
    }
    return true;
}

/**
 * 
 * @param {BigInt} n 
 * @param {BigInt} k 
 */
function main(n, k) {
    // 1 如果 k + 1 是质数
    // a 如果 n 中没有 k + 1 的倍数，一次即可
    // b 如果 n 中有 k + 1 的倍数，那么就要两次
    // 2 如果 k + 1 是合数
    //   根据 伯特兰-切比雪夫定理 ，必定存在一个质数
    // 第一次选择一个质数，第二次同 1a，共两次。
    // 综上，若 k + 1 满足 1a ，则一次，其余二次

    if (isPrime(k + 1n) && 2n * k >= n) {
        console.log(1);
    } else {
        console.log(2);
    }
}

readline.on('line', (input) => {
    const [n, k] = input.split(" ").map(BigInt);
    main(n, k);
    readline.close();
});