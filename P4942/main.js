const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

let n;

function runn(input) {
    const arr = input.split(" ").map(BigInt);
        const left = arr[0], right = arr[1];
        
        let x, y;

        if ((left + right) % 2n === 0n) {
            x = (left + right) / 2n;
            y = right - left + 1n;
        } else {
            x = left + right;
            y = (right - left + 1n) / 2n;
        }

        const ans = ((x % 9n) * (y % 9n)) % 9n;
        console.log(String(ans));
}


readline.on('line', (input) => {
    if (!n) {
        n = parseInt(input);
        return;
    }
    n--;
    runn(input);
    if (n === 0) {
        readline.close();
    }
});
