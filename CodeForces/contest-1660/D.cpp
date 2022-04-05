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
    Range(int l_ = 0, int r_ = 0, int val_ = 1) : l(l_), r(r_), val(val_) {} 
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
        
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == 0 || i + 1 == n)
            {
                // 分割当前数组
                
                if (now.val < 0)
                {
                    int l = now.l, r = now.r;
                    int cntl = 1, cntr = 1;
                    while (0 < arr[l])
                    {
                        cntl *= arr[l];
                        l++;
                    }
                    while (0 < arr[r])
                    {
                        cntr *= arr[r];
                        r--;
                    }
                    if (cntl * arr[l] < cntr * arr[r]) 
                    {
                        // 删掉右侧留下的大
                        now = Range(now.l, r, now.val / cntr);
                    }
                    else
                    {
                        now = Range(l, now.r, now.val / cntl);
                    }
                }
                if (ans.val < now.val)
                {
                    ans = now;
                }
                now = Range(i + 1, i + 1, 1);
            }
            else
            {
                now.val *= arr[i];
                now.r = i;
            }
        }
        cout << ans.l << (n - ans.r - 1) << "\n";
    }
    return 0;
}