#include <cstddef>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using std::cin;
using std::lower_bound;
using std::upper_bound;
using std::cout;
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

const int MAXN = 3e5 + 2, MAXK = 1e6 + 2;

int vals[MAXN], valSum[MAXN];
std::map<int, std::vector<int> > deToNode;
bool rankTag[MAXN];
int n, m, k;

int main()
{
#ifdef MY_DEBUG
std::freopen("sakura.in", "r", stdin);
std::freopen("sakura.out", "w", stdout);
#endif
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        int now;
        cin >> now;
        rankTag[now] = true;
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> vals[i];
        vals[i] %= k;
        valSum[i] =  valSum[i-1] + vals[i];
        if (rankTag[i])
        {
            deToNode[valSum[i] % k].push_back(i);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        auto & vec = deToNode[0];
        auto it = lower_bound(vec.begin(), vec.end(), i);
        int lsum = 0;
        if (it != vec.end())
        {
            lsum = it - vec.begin();
        }

        auto & vecR = deToNode[vals[i]];
        auto itR = upper_bound(vecR.begin(), vecR.end(), i);
        int rsum = 0;
        if (itR != vecR.end())
        {
            rsum = (vecR.size() - (itR - vecR.begin()));
        }
        ans = max(ans, lsum + rsum);
    }
    cout << ans << "\n";
    return 0;
}   
