#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using std::queue;
using std::shared_ptr;
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

/**
 * @brief 把一个点拆成两个点，这样就可以把节点的容量换成边的容量，每次跑出来的网络流就是最大的连接的点的个数了
 *
 */
class MyFlow : public GetNetFlow
{
    int add;

    void reset(int i)
    {
        for (auto& p : graph)
        {
            for (auto& e : p)
            {
                e->flow = 0;
            }
        }
        GetNetFlow::addEdge(i, i + add, INF);
    }

    void rmEdge(int i)
    {
        graph[i].pop_back();
        graph[i + add].pop_back();
    }

   public:
    MyFlow(int n_) : GetNetFlow(n_ * 2 + 10), add(n_)
    {
        // 初始化拆分后的节点
        for (int i = 0; i < n_; i++)
        {
            GetNetFlow::addEdge(i, i + add, 1);
        }
    }

    void addEdge(int from, int to)
    {
        GetNetFlow::addEdge(from + add, to, 1);
        GetNetFlow::addEdge(to + add, from, 1);
    }

    long long getMaxFlow(int s, int t)
    {
        // 预先把终点设置成无穷大，这样可以让其他点流得进来
        reset(t);
        auto rt = GetNetFlow::getMaxFlow(s + add, t + add);
        rmEdge(t);
        return rt;
    }
};

const int MAXN = 50 + 2;

int main()
{
    std::ios::sync_with_stdio(false);
    auto rdOther = []()
    {
        while (!std::isdigit(cin.peek()))
        {
            cin.get();
        }
    };
    int n, m;
    // 拆点法，使用拆点来给每个节点分配 1 的容量，然后跑网络流，求最小割的大小
    while (cin >> n >> m)
    {
        if (n <= 1)
        {
            cout << n << '\n';
            continue;
        }
        MyFlow gf(n);
        vector<vector<bool>> graph(n+1, vector<bool>(n+1, false));
        for (int i = 0; i < m; i++)
        {
            // format (XX,XX)
            int u, v;
            rdOther();
            cin >> u;
            rdOther();
            cin >> v;
            cin.get();

            graph[u][v] = 1;
            graph[v][u] = 1;

            gf.addEdge(u, v);
        }
        long long ans = n;
        // 对于每个不直接相连的边，对他们进行一个网络流，取最小的答案
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (!graph[i][j])
                {
                    ans = min(ans, gf.getMaxFlow(i, j));
                }
            }
        }

        cout << ans << '\n';
    }
    return 0;
}