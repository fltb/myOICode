#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using std::queue;
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
    struct MSEdge
    {
        int from, to, capacity, flow;
        MSEdge* opposite;
        MSEdge(int from_ = 0, int to_ = 0, int capacity_ = 0, int flow_ = 0) : from(from_), to(to_), capacity(capacity_), flow(flow_), opposite(NULL) {}
    };
    size_t n;
    vector<vector<MSEdge*> > graph;
    vector<MSEdge> edges;

    // ERR 因为变量的二次释放，被迫搞成这样
    // ERR 全部改成指针了
    vector<int> flows;
    vector<MSEdge*>  parentEdge;
   public:
   ~GetNetFlow() {}
    GetNetFlow() {}
    void build(size_t n)
    {
        graph = vector<vector<MSEdge*> >(n + 1, vector<MSEdge*>());
        edges = vector<MSEdge>();
        // ERR 这是 STL 的问题了
        edges.push_back(MSEdge());
    }

    void addEdge(int from, int to, int capacity)
    {
        edges.push_back(MSEdge(from, to, capacity, 0));
        auto * e1 = &edges.back();
        graph[from].push_back(e1);
        edges.push_back(MSEdge(to, from, 0, 0));
        auto * e2 = &edges.back();
        graph[to].push_back(e2);
        e1->opposite = e2;
        e2->opposite = e1;
    }

    auto getMaxFlow(int s, int t)
    {
        auto allFlow = 0ll;
        // 一个 BFS， 每次跑一个增广路，然后记下它的流量，扣除每条边的流量
        flows = vector<int>(n + 1, 0);
        parentEdge = vector<MSEdge*>(n + 1, 0);

        auto finding = [&]()
        {
            vector<bool> vis(n + 1, false);
            queue<size_t> js;

            js.push(s);
            vis[s] = 1;
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
GetNetFlow gf;
int main()
{
    std::ios::sync_with_stdio(false);
    int n, e, s, t;
    cin >> n >> e >> s >> t;
    gf.build(n+1);
    for (int i = 0; i < e; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        gf.addEdge(u, v, c);
    }
    cout << gf.getMaxFlow(s, t) << std::endl;
    exit(0);
    return 0;
}