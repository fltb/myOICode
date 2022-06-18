
/*
https://www.luogu.com.cn/problem/P2471
*/
#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <set>
using std::cout;
using std::cin;
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::log2;
inline int max(int a, int b) { return a < b ? b : a; }
const int MAXN = 50000 + 2,
          MAXNLOG2 = 16 + 1;

class MyStruct
{
public:
    // use this to save datas
    int dp[MAXN][MAXNLOG2];
    set<int> years;
    map<int, int> year2cur;

    int get_cur(int year, bool prevers)
    {
        int cur;
        if (has_space(year))
        {
            auto it = years.insert(year).first;
            if (prevers)
            {
                --it;
                cur = year2cur[*it];
                ++it;
            }
            else
            {
                ++it;
                cur = year2cur[*it];
                --it;
            }
            years.erase(it);
        }
        else
        {
            cur = year2cur[year];
        }
        return cur;
    }

    void init(const vector<pair<int, int> > & a) // first year second val
    {
        size_t total = a.size();
        for (size_t i = 0; i < total; ++i)
        {
            years.insert(a[i].first);
            year2cur[a[i].first] = i + 1;
            dp[i + 1][0] = a[i].second;
        }

        for (int lg = 1; (1<<(lg)) <= total; ++lg)
        {
            int len = (1<<lg);
            int len_son = (len>>1);
            for (int i = 1; i + len - 1 <= total; ++i)
            {
                int j = i + len_son;
                dp[i][lg] = max(dp[i][lg-1], dp[j][lg-1]);
            }
        }
    }

    bool has_space(int year)
    {
        return !years.count(year);
    }

    bool has_space(int year_begin, int year_end)
    {
        if (has_space(year_begin) ||has_space(year_end))
        {
            return true;
        }

        int cur_begin = year2cur[year_begin];
        int cur_end = year2cur[year_end];

        if (year_end - year_begin > cur_end - cur_begin)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int get_val(int year)
    {
        if (has_space(year))
        {
            // OMG
            throw "YEAR_NOT_EXSIST";
        }
        int cur = year2cur[year];
        return dp[cur][0];
    }

    int get_val(int year_begin, int year_end)
    {
        int cur_begin = get_cur(year_begin, false);
        int cur_end = get_cur(year_end, true);

        int lg = log2(cur_end - cur_begin + 1);

        int i = cur_begin;
        int j = cur_end - (1<<lg) + 1;

        return max(dp[i][lg], dp[j][lg]);
    }
};

MyStruct ms;

int main()
{
    #ifdef LOCAL 
    std::freopen("1.in", "r", stdin);
    std::freopen("1.out", "w", stdout);
    #endif

    std::ios::sync_with_stdio (false);
    int n;
    cin >> n;
    vector<pair<int, int> > arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].first >> arr[i].second;
    }
    ms.init(arr);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int year_begin, year_end;
        cin >> year_begin >> year_end;

        // judge false
        if (year_begin >= year_end)
        {
            cout << "false\n";
            continue;
        }

        // 如果是两个都是极限

        if (year_end <= *ms.years.begin())
        {
            cout << "maybe\n";
            continue;
        }

        if (year_begin >= *ms.years.rbegin())
        {
            cout << "maybe\n";
            continue;
        }

        // 两个端点都是不确定
        if (ms.has_space(year_begin) && ms.has_space(year_end))
        {
            cout << "maybe\n";
            continue;
        }

        // 左右有极限值
        if (year_begin < *ms.years.begin() && ms.get_cur(year_end, true) == ms.get_cur(*ms.years.begin(), true))
        {
            cout << "false\n";
            continue;
        }

        if (year_end > *ms.years.rbegin() && ms.get_cur(year_begin, false) == ms.get_cur(*ms.years.end(), false))
        {
            cout << "false\n";
            continue;
        }

        // 如果不存在中间
        if (ms.get_cur(year_begin + 1, false) > ms.get_cur(year_end -1 ,true))
        {
            if (ms.has_space(year_begin) || ms.has_space(year_end))
            {
                cout << "maybe\n";
            }
            else if (ms.get_val(year_begin) < ms.get_val(year_end))
            {
                cout << "false\n";
            }
            // 对着数据调的，玄学
            else if (ms.has_space(year_begin, year_end))
            {
                cout << "maybe\n";
            }
            else
            {
                cout << "true\n";
            }
            continue;
        }
        else // 存在中间的
        {
            bool lexsist = !ms.has_space(year_begin);
            bool rexsist = !ms.has_space(year_end);
            bool midspace = ms.has_space(year_begin + 1, year_end - 1);
            int lval, rval, midval;
            if (lexsist)
            {
                lval = ms.get_val(year_begin);
            }
            if (rexsist)
            {
                rval = ms.get_val((year_end));
            }
            midval = ms.get_val(year_begin + 1, year_end - 1);

            // falses
            if (rexsist && midval >= rval)
            {
                // 右边存在，中间大于等于右边
                cout << "false\n";
                continue;
            }
            if (lexsist && midval >= lval)
            {
                // 左边存在，中间大于等于左边
                cout << "false\n";
                continue;
            }
            if (lexsist && rexsist && lval < rval)
            {
                // 左右存在，左小于右
                cout << "false\n";
                continue;
            }
            //maybes
            if (!lexsist || !rexsist)
            {
                cout << "maybe\n";
                continue;
            } 
            if (ms.has_space(year_begin + 1, year_end - 1))
            {
                // 中间有空
                cout << "maybe\n";
                continue;
            }
            // 最后了，肯定是true
            cout << "true\n";
        }
    }

    return 0;
}