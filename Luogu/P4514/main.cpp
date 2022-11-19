#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#define cosnt const
using std::cin;
using std::cout;
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
const int MAXN = 2048 + 2;
long long a[MAXN][MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    cin.get();
    int n, m;
    cin >> n >> m;
    char ch;
    while (cin >> ch) {
        int x1,y1,x2,y2,in;
        if (ch == 'L') {
            
            cin >> x1 >> y1 >> x2 >> y2 >> in;
            for (int i = x1; i <= x2;i++){
                for (int j=y1;j<=y2;j++){
                    a[i][j] += in;
                }
            }
        } else {
            cin >> x1>>y2>>x2>>y2;
            long long sum=0;
            for (int i = x1; i <= x2;i++){
                for (int j=y1;j<=y2;j++){
                   sum+=a[i][j];
                }
            }
            cout << sum << '\n';
        }
    }
    return 0;
}