const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});
  
let myAPP = {
    cnt: 0,
    a: 0n,
    b: 0n
};

readline.on('line', (inget) => {
    inget = BigInt(inget);
    if (myAPP.cnt === 0) {
        myAPP.a = inget;
        myAPP.cnt = 1;
    } else {
        myAPP.b = inget;
        readline.close();
    }
});

readline.on('close', () => {
    let a = myAPP.a;
    let b = myAPP.b;
    let prtans = function(arg) {
        let ans = arg.toString();
        console.log(ans);
    }
    prtans(a+b);
    prtans(a-b);
    prtans(a*b);
    prtans(a/b);
    prtans(a%b);
});
