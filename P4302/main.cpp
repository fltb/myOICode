#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int min(int a, int b) {
    return a < b ? a : b;
}
const int MAXN = 100 + 2,
          INF = 214748364;

string str;
int f[MAXN][MAXN]; // close range

void initf() {
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
                f[i][j] = INF;
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        f[i][i] = 1;
    }
}

bool is_foldable(int i, int j, int len) {
    if ((j - i + 1) % len) {
        return false;
    }
    for (int cur = i; cur <= j; ++cur) {
        if (str[cur] != str[(cur - i) % len + i]) {
            return false;
        }
    }
    return true;
}

int get_int_length(int x) {
    if (x < 10) {
        return 1;
    } else if (x < 100) {
        return 2;
    } else {
        return 3;
    }
}


int main() {
    initf();
    cin >> str;
    for (size_t len1 = 2; len1 <= str.length(); ++len1) {
        for (size_t i = 0; i + len1 - 1 < str.length(); ++i) {
            size_t j = i + len1 - 1;
            for (size_t k = i; k < j; ++k) { 
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
            for (size_t len2 = 1; len2 <= len1; ++len2) {
                size_t k = i + len2 - 1;
                if (is_foldable(i, j, len2)) {
                    f[i][j] = min(f[i][j], get_int_length(len1 / len2) + 2 + f[i][k]);
                }
            }
        }
    }
    cout << f[0][str.length()-1] << endl;
    return 0;
}