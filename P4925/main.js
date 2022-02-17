"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

let Float = {
    k: 0,
    l: 0,
    mod: 0,
    m: 0,
    cnt: 0,
    quickPow: function(a, b) {
        let sum = 1n;
        const mod = this.mod;
        a %= mod;
        while (b > 0n) {
            if (b & 1n) {
                sum = sum * a % mod;
            }
            b >>= 1n;
            a = a * a % mod;
        }
        return sum;
    },
    solve: function() {
        let {k, l, mod, m} = this;
        if (l === 1n) {
            if (m) {
                console.log(1n % mod);
            } else {
                console.log(k % mod);
            }
            return;
        }
        k %= mod;
        let ans;
        if (m) {
            ans = (k - 1n) % mod;
        } else {
            ans = k * (k - 1n) % mod;
        }
        ans = (ans * this.quickPow(k - 2n, l - 2n)) % mod;
        console.log(String(ans));
    }
};

readline.on('line', (input) => {
    if (Float.cnt === 0) {
        Float.cnt++;
        [Float.k, Float.l, Float.mod] = input.split(" ").map(BigInt);
    } else {
        Float.m = input.split(" ").map(BigInt)[0];
        Float.solve();
        readline.close();
    }
    
});