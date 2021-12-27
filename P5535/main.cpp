// JS TLE 了，，，只能用 CPP 了
#include <iostream>

bool isPrime(long long a) {
    if (a == 1) {
        return false;
    }
    if (a == 2) {
        return true;
    }
    for (long long i = 2; i * i <= a; ++i) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

void run(long long n, long long k) {
    // 1 如果 k + 1 是质数
    // a 如果 n 中没有 k + 1 的倍数，一次即可
    // b 如果 n 中有 k + 1 的倍数，那么就要两次
    // 2 如果 k + 1 是合数
    //   根据 伯特兰-切比雪夫定理 ，必定存在一个质数
    // 第一次选择一个质数，第二次同 1a，共两次。
    // 综上，若 k + 1 满足 1a ，则一次，其余二次

    if (isPrime(k + 1) && 2 * k >= n) {
        std::cout << 1;
    } else {
        std::cout << 2;
    }
}

int main() {
    long long n, k;
    std::cin >> n >> k;
    run(n, k);
    return 0;
}
