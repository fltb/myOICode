
/*
https://www.luogu.com.cn/problem/P2471
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
using std::cout;
using std::cin;
using std::endl;
const int MAXN = 50000 + 2,
          MAXNLOG2 = 16 + 1;

struct MyStruct
{
    using namespace std;
    // use this to save datas
    int dp[MAXN][MAXNLOG2];
    set<int> years;
    map<int> year2cur;
    void init(const vector<pair<int, int> > & a) // first year second val
    {
        size_t total = a.size();
        for (size_t i = 0; i < total; ++i)
        {
            year2cur[a[i].first] = i + 1;
            dp[i + 1][i + 1] = a[i].second;
        }

        
    }
};

int main()
{

}