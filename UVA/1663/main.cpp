#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <vector>
using std::cin;
using std::cout;
using std::queue;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

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
const int INF = 0x3f3f3f3f;
class GetNetFlow
{
   protected:
    struct MSEdge
    {
        int from, to, capacity, flow;
        shared_ptr<MSEdge> opposite;
        MSEdge(int from_ = 0, int to_ = 0, int capacity_ = 0, int flow_ = 0) : from(from_), to(to_), capacity(capacity_), flow(flow_), opposite(nullptr) {}
    };
    size_t n;
    vector<vector<shared_ptr<MSEdge>>> graph;

    // ERR 全部改成指针了
   public:
    // ERR n 没有初始化
    GetNetFlow(size_t n_) : n(n_), graph(n_ + 1, vector<shared_ptr<MSEdge>>()) {}

    void addEdge(int from, int to, int capacity)
    {
        // ERR !!! edges 再次 push_back 之后，e1 指向的值变了！！！
        // 而且只有第一次 push 会出问题！
        // 所以我换成智能指针了
        shared_ptr<MSEdge> e1(new MSEdge(from, to, capacity, 0));
        shared_ptr<MSEdge> e2(new MSEdge(to, from, 0, 0));
        e1->opposite = e2;
        e2->opposite = e1;
        graph[from].push_back(e1);
        graph[to].push_back(e2);
    }

    long long getMaxFlow(int s, int t)
    {
        auto allFlow = 0ll;
        vector<int> flows(n + 1, 0);
        vector<shared_ptr<MSEdge>> parentEdge(n + 1, nullptr);

        // 一个 BFS， 每次跑一个增广路，然后记下它的流量，扣除每条边的流量

        auto finding = [&]()
        {
            vector<bool> vis(n + 1, false);
            queue<size_t> js;

            js.push(s);
            vis[s] = true;
            flows[s] = INF;
            while (!js.empty())
            {
                // 取出队首节点，尝试它的所有边，看看能不能到达新的节点，如果可以，更新它的值，把它加进队列
                const auto nd = js.front();
                js.pop();

                for (auto ep : graph[nd])
                {
                    auto u = ep->from, v = ep->to;
                    if (ep->capacity > ep->flow && !vis[v])
                    {
                        vis[v] = true;
                        flows[v] = min(flows[u], ep->capacity - ep->flow);
                        parentEdge[v] = ep;
                        js.push(v);
                        if (v == t)
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        };

        while (finding())
        {
            // 得到当前的流大小，加进统计当中，再把边更新一下
            auto flow = flows[t];
            allFlow += flows[t];
            auto jump = t;
            do
            {
                auto pe = parentEdge[jump];
                auto peo = pe->opposite;

                pe->flow += flow;
                peo->flow -= flow;

                jump = pe->from;

                // ERR jump == s
            } while (jump != s);
        }

        return allFlow;
    }
};

auto cntbit = [](int n)
{
    int cnt = 0;
    while (n)
    {
        n &= n - 1;
        cnt++;
    }
    return cnt;
};

auto is2pow = [](int n)
{
    return cntbit(n) == 1;
};

class MyFlow : public GetNetFlow
{
    int add, ss, tt;

   public:
    MyFlow(int n_) : GetNetFlow(n_ * 2 + 10), add(n_) {}
    void build(const set<int> & st)
    {
        ss = st.size() * 2 + 1, tt = st.size() * 2 + 2;
        int i = 0;
        for (auto & tem : st)
        {
            if (cntbit(tem) % 2 == 1)
            {
                addEdge(i, tt, 1);
            }
            else
            {
                addEdge(ss, i, 1);
            }
            int j = 0;
            for (auto & tem2 : st)
            {
                if (is2pow(tem ^ tem2))
                {
                    if (cntbit(tem2) % 2 == 1)
                    {
                        addEdge(i, j, 1);
                    }
                    else
                    {
                        addEdge(j, i, 1);
                    }
                }
                j++;
                if (j >= i)
                {
                    break;
                }
            }
            i++;
        }
    }
    long long getAns()
    {
        return getMaxFlow(ss, tt);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    int m;

    while (cin >> n && cin >> m && n && m)
    {
        cin.get();
        set<int> templs;
        auto ins = [&templs](int x)
        {
            if (!templs.count(x))
            {
                templs.insert(x);
            }
        };
        for (int i = 0; i < m; i++)
        {
            string str;
            cin >> str;
            cin.get();
            int t1 = 0, t2 = 0;
            for (auto& ch : str)
            {
                // 把 *  变成 0
                t1 = (t1 << 1) | (ch == '1');
                // 把 * 变成 1
                t2 = (t2 << 1) | (ch != '0');
            }
            ins(t1);
            ins(t2);
        }
        MyFlow mf(templs.size() + 1);
        mf.build(templs);
        cout << templs.size() - mf.getAns() << '\n';
    }
    return 0;
}