#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template<typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}
const int MAXW = 4e4 + 2;
struct Item {
    int v, w;
    Item(int v_=0, int w_=0) : v(v_), w(w_) {}
};
int main()
{
    std::ios::sync_with_stdio(false);

    int n, W;
    cin >> n >> W;

    vector<Item> arr;
    for (int i = 0; i < n; i++)
    {
        long long w, v;
        int t;
        cin >> v >> w >> t;

        int basev = 1, basew = w;
        for(int j=1;j<=t;j<<=1)
        {
            basev=j*v,basew=j*w;
            arr.push_back(Item(basev, basew));
            t -= j;
        }
        if(t) arr.push_back(Item(v * t, w * t)); //v[++cnt]=a*c,w[cnt]=b*c;

    }

    vector<int> dp(W + 2, 0);
    for (auto item : arr)
    {
        for (int j = W; j >= item.w; j--)
        {
            dp[j] = max(dp[j], dp[j - item.w] + item.v);
        }
    }

    cout << dp[W] << "\n";

    return 0;
}