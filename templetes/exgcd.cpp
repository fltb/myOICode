#include <iostream>
#include <utility>
using std::pair;
using std::make_pair;

pair<int, int> exgcd(int a, int b)
{
    if (b == 0)
    {
        return make_pair(1, 0);
    }
    auto ans = exgcd(a, a % b);
    int x = ans.second;
    int y = ans.first - (a / b) * ans.second;
    return make_pair(x, y);
}
