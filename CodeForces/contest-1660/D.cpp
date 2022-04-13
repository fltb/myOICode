#include <iostream>
#include <algorithm>
using std::cin;
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

struct Range {
    int l, r, val;
    bool flag;
    Range(int l_ = 0, int r_ = 0, int val_ = 0, bool flag_ = true) : l(l_), r(r_), val(val_), flag(flag_) {} 
    bool operator<(const Range & x) const 
    {
        if (flag ^ x.flag)
        {
            return !flag;
        }
        else
        {
            if (flag)
            {
                return val < x.val;
            }
            else
            {
                return !(val < x.val);
            }
        }
    }
};
const int MAXN = 2e5 + 2;
int arr[MAXN];
/*
解法：
只能遍历数组，不涉及暴力枚举区间的操作（即 O(n) 做法）

最后的权值肯定大于等于 1，那么 0 应该完全去除，即遇到 0 则分割。
答案一定是正数，而且整数乘法不会越乘越小，所以去掉负数就可以了。
*/
int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {  
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        auto ans = Range();
        auto now = Range();
        bool flag = false;
        auto is2 = [](int x) {  return int(x == 2 || x == -2);  };
        for (int i = 0; i < n; i++)
        {
            if (arr[i] != 0)
            {
                now.val += is2(arr[i]);
                now.flag = ((now.flag && arr[i] > 0) || (!now.flag && arr[i] < 0));
            }
            if (arr[i] == 0 || i + 1 == n)
            {
                if (arr[i] == 0)
                {
                    now.r--;
                }
                if (now.l > now.r)
                {
                    continue;
                }
                // 分割当前数组
                if (!now.flag)
                {
                    int l = now.l, r = now.r;
                    int cntl = 0, cntr = 0;

                    while (0 < arr[l]) {
                        cntl += is2(arr[l]);
                        l++;
                    }
                    cntl += is2(arr[l]);

                    while (0 < arr[r]) {
                        cntr += is2(arr[r]);
                        r--;
                    }
                    cntr += is2(arr[r]);

                    if (cntr < cntl) 
                    {
                        // 删掉右侧留下的大
                        now = Range(now.l, r - 1, now.val - cntr, true);
                    }
                    else
                    {
                        now = Range(l + 1, now.r, now.val - cntl, true);
                    }
                }
                if (ans < now)
                {
                    ans = now; flag = true;
                }
                now = Range(i + 1, i + 1, 0, true);
                continue;
            }
            now.r++;
        }
        cout << ans.l << " " << ( flag ? (n - ans.r - 1) : n) << "\n";
    }
    return 0;
}