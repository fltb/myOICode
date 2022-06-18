"use strict";

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

let Float = {
    LENGTH: 13,
    init: function () {
        this.arrTable = [];
        this.arrTable[1] = 1;
        for (let len = 2; len < this.LENGTH; len++) {
            this.arrTable[len] = this.arrTable[len - 1] * 10 + Math.pow(10, len - 1);
        }
    },

    solve: function (a) {
        let numBit = [],
            numCut = [],
            arr = [];
        for (let i = 0; i < this.LENGTH; i++) {
            arr[i] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        }
        let cnt = 0;
        let b = a;
        while (b > 0) {
            numBit[++cnt] = b % 10;
            b = Math.floor(b/10);
        }
        for (let i = 1; i <= cnt; i++) {
            numCut[i] = a % Math.pow(10, i);
            numCut[i]++;
        }

        // dp start
        // dp init
        for (let i = 0; i <= numBit[1]; i++) {
            arr[1][i] = 1;
        }

        const arrTable = this.arrTable;
        for (let len = 2; len <= cnt; len++) {
            for (let i = 0; i < 10; i++) {
                arr[len][i] = numBit[len] * arrTable[len - 1] + arr[len - 1][i];
                if (i < numBit[len]) {
                    arr[len][i] += Math.pow(10, len - 1);
                } else if (i === numBit[len]) {
                    arr[len][i] += numCut[len - 1];
                }
            }
        }

        // clear 0
        for (let len = cnt; len > 1; len--) {
            for (let i = len; i <= cnt; i++) {
                arr[i][0] -= Math.pow(10, len - 1);
            }
        }
        if (cnt === 0) {
            cnt === 1;
        }
        return arr[cnt];
    },
    
    getAns: function(a, b) {
        this.init();
        let arr1 = this.solve(b);
        let arr2 = this.solve(a-1);
        for (let i = 0; i < 10; i++) {
            if (arr2[i]) {
                arr1[i] -= arr2[i];
            }
        }
        return arr1;
    }
};

readline.on('line', (input) => {
    const [n, m] = input.split(" ").map(Number);
    console.log(Float.getAns(n, m).join(" "));
    readline.close();
});


