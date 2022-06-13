/**
 *
 *
 *
 * 题目描述

在一个平面直角坐标系上，有 nnn 个矩形，这些矩形的底边都靠在的 X 轴上。其中第 iii 个矩形的底边在 X 轴上，覆盖了从 sis_isi​ 到 tit_iti​ 的坐标，这个矩形的高为 hih_ihi​。

请统计这些矩形覆盖的总面积是多少（重复覆盖的部分只算一次）。
输入格式

第一行：单个整数 nnn
第二行到第 n+1n+1n+1 行，第 iii 行有三个整数表示 si,tis_i, t_isi​,ti​ 与 hih_ihi​
输出格式

单个整数：表示这些矩形覆盖的总面积。
数据范围
    对于 30%30\%30% 的数据，1≤n≤5001\leq n\leq 5001≤n≤500，1≤si,ti,hi≤5001\leq s_i,t_i,h_i\leq 5001≤si​,ti​,hi​≤500；
    对于 60%60\%60% 的数据，1≤n≤10,0001\leq n\leq 10,0001≤n≤10,000；
    对于 100%100\%100% 的数据，1≤n≤300,0001\leq n\leq 300,0001≤n≤300,000；
    1≤si,ti,hi≤1091\leq s_i, t_i,h_i\leq 10^91≤si​,ti​,hi​≤109。

 */

#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <set>
using std::cin;
using std::cout;
using std::set;
using std::sort;
template <typename T>
inline T max(T a, T b)
{
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b)
{
    return a < b ? a : b;
}
const int MAXN = 300000 + 5;
enum RecDir
{
    LEFT,
    RIGHT
};
struct NodeJS
{
    int l, r, h;
    NodeJS(int l_ = 0, int r_ = 0, int h_ = 0) : l(l_), r(r_), h(h_) {}
    bool operator<(const NodeJS& nd) const
    {
        if (h < nd.h)
        {
            return true;
        }
        else if (h == nd.h)
        {
            return l < nd.l;
        }
        else
        {
            return false;
        }
    }
};

struct Record
{
    int x;
    const NodeJS* nd;
    Record(int x_ = 0, const NodeJS* nd_ = nullptr) : x(x_), nd(nd_) {}
    int atLR() const
    {
        return (x == nd->l ? LEFT : RIGHT);
    }
    bool operator<(const Record& rc) const
    {
        if (x < rc.x)
        {
            return true;
        }
        else if (x == rc.x)
        {
            return *nd < *rc.nd;
        }
        else
        {
            return false;
        }
    }
};

NodeJS arr[MAXN];
int cntArr;

Record recs[MAXN * 2];
int rcnt;
int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r, h;
        cin >> l >> r >> h;
        arr[i] = NodeJS(l, r, h);
    }

    for (int i = 0; i < n; i++)
    {
        const auto* now = &arr[i];
        recs[rcnt++] = Record(now->l, now);
        recs[rcnt++] = Record(now->r, now);
    }

    sort(recs, recs + rcnt);

    long long ans = 0ll;
    set<NodeJS> st;
    st.insert(*recs[0].nd);
    for (int i = 1; i < rcnt; i++)
    {
        const auto& now = recs[i];
        const auto& pre = recs[i - 1];
        ans += st.rbegin()->h * (now.x - pre.x);
        if (now.atLR() == LEFT)
        {
            st.insert(*now.nd);
        }
        else
        {
            st.erase(st.find(*now.nd));
        }
    }

    cout << ans << '\n';
    return 0;
}