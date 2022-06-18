const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

readline.on('line', (input) => {
    let arr = input.split(" ");
    let a = BigInt(arr[0]), b = BigInt(arr[1]);
    console.log(String(a * b - a - b));
    readline.close();
});
