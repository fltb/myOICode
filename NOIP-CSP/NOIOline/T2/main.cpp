#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::map;
using std::set;
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

int main()
{
    std::freopen("discuss.in", "r", stdin);
    std::freopen("discuss.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        if (n > 5001)
        {
            for (int i = 1; i <= n; i++)
            {

                int c;
                cin >> c;
                while (c--)
                {
                    int pid;
                    cin >> pid;
                }
            }
            cout << "NO\n";
        }
        map<int, set<int> > ptom;
        map<int, set<int> > mtop;
        int flag = 0, p1 = 0, p2 = 0;
        for (int i = 1; i <= n; i++)
        {
            map<int, int> mtocnt;
            set<int> everhad;
            set<int> disabled;
            int c;
            cin >> c;
            while (c--)
            {
                int pid;
                cin >> pid;
                if (flag)
                {
                    continue;
                }
                map<int, bool> tmp;
                if (ptom.find(pid) != ptom.end())
                {
                    for (int man : ptom[pid])
                    {
                        if (!everhad.count(man))
                        {
                            everhad.insert(man);
                        }
                        if (!disabled.count(man))
                        {
                            mtocnt[man]++;
                            tmp[man] = true;
                        }
                    }
                }
                for (int man : everhad)
                {
                    if (tmp.find(man) == tmp.end())
                    {
                        if (mtop[man].size() == mtocnt[man])
                        {
                            disabled.insert(man);
                            continue;
                        }
                        else
                        {
                            flag = true;
                            p1 = man;
                            p2 = i;
                            break;
                        }
                    }
                }
                ptom[pid].insert(i);
                mtop[i].insert(pid);
            }
        }
        if (!flag)
        {
            cout << "NO" << "\n";
        }
        else
        {
            cout << "YES" << "\n"
                 << p1 << " " << p2 << "\n";
        }
    }
    return 0;
}