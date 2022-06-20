#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
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
    struct MSEdge
    {
        int from, to, capacity, flow, cost;
        shared_ptr<MSEdge> opposite;
        MSEdge(int from_ = 0, int to_ = 0, int capacity_ = 0, int flow_ = 0, int cost_ = 0) : from(from_), to(to_), capacity(capacity_), flow(flow_), cost(cost_), opposite(nullptr) {}
    };

    size_t n;
    vector<vector<shared_ptr<MSEdge>>> graph;

    // ERR 全部改成指针了
   public:
    // ERR n 没有初始化
    GetNetFlow(size_t n_) : n(n_), graph(n_ + 1, vector<shared_ptr<MSEdge>>()) {}

    void addEdge(int from, int to, int capacity, int cost)
    {
        // ERR !!! edges 再次 push_back 之后，e1 指向的值变了！！！
        // 而且只有第一次 push 会出问题！
        // 所以我去掉 edges 的 vector， 全部用智能指针了
        shared_ptr<MSEdge> e1(new MSEdge(from, to, capacity, 0, cost));
        shared_ptr<MSEdge> e2(new MSEdge(to, from, 0, 0, 0 - cost));
        e1->opposite = e2;
        e2->opposite = e1;
        graph[from].push_back(e1);
        graph[to].push_back(e2);
    }

    /**
     * @brief Get the Max Flow and Minimal Costs
     *
     * @param s
     * @param t
     * @return std::pair<long long, long long> - flows, costs
     */
    std::pair<long long, long long> getMaxFlow(int s, int t)
    {
        auto allFlow = 0ll, allCosts = 0ll;
        vector<int> distance(n + 1, INF);
        vector<int> flows(n + 1, 0);
        vector<shared_ptr<MSEdge>> parentEdge(n + 1, nullptr);

        // 一个 Bellman-Flod，每次算一条可以达到的最短路，一直到全部都好了
        auto bellmenFlod = [&]()
        {
            distance = vector<int>(n + 1, INF);
            vector<int> cnting(n + 1, 0);
            vector<bool> inQueue(n + 1, false);
            queue<size_t> js;

            js.push(s);
            flows[s] = INF;
            distance[s] = 0;

            while (!js.empty())
            {
                // 取出队首节点，尝试它的所有边，看看能不能覆盖掉先前的最小值，如果可以，更新它目标的最小值，把它加进队列
                const auto nd = js.front();
                js.pop();
                inQueue[nd] = false;
                for (auto ep : graph[nd])
                {
                    auto u = ep->from, v = ep->to;
                    // ERR flowing = ep->capacity > ep->flow
                    auto flowing = ep->capacity - ep->flow;
                    // ERR distance[u] + ep->cost * flowing
                    if (flowing > 0 && distance[v] > distance[u] + ep->cost)
                    {
                        flows[v] = min(flows[u], ep->capacity - ep->flow);
                        distance[v] = distance[u] + ep->cost;
                        parentEdge[v] = ep;
                        if (cnting[v]++ > n)
                        {
                            // 负环
                            return false;
                        }
                        if (!inQueue[v])
                        {
                            inQueue[v] = true;
                            js.push(v);
                        }
                    }
                }
            }
            return bool(cnting[t]);
        };

        while (bellmenFlod())
        {
            // 得到当前的流大小，加进统计当中，再把边更新一下
            auto flow = flows[t];
            allFlow += flows[t];
            allCosts += distance[t] * flow;
            auto jump = t;
            do
            {
                auto pe = parentEdge[jump];
                auto peo = pe->opposite;

                pe->flow += flow;
                peo->flow -= flow;
                /**ERR
                 * peo->cost = 0-peo->cost;
                 * pe->cost = 0-pe->cost;
                 */
                jump = pe->from;

                // ERR jump == s
            } while (jump != s);
        }

        return std::make_pair(allFlow, allCosts);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    int n, e, s, t;
    cin >> n >> e >> s >> t;
    GetNetFlow gf(n);
    for (int i = 0; i < e; i++)
    {
        int u, v, cap, c;
        cin >> u >> v >> cap >> c;
        gf.addEdge(u, v, cap, c);
    }
    auto rts = gf.getMaxFlow(s, t);
    cout << rts.first << " " << rts.second << std::endl;
    return 0;
}