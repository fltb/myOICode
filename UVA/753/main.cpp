#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::map;
using std::queue;
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
        if (from == to)
        {
            return;
        }
#ifdef FLOATINGBLOCK
        cout << "edge " << from << " " << to << '\n';
#endif
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
#ifdef FLOATINGBLOCK
                cout << "jumping " << jump << '\n';
#endif
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

class GetNetFlowSt : public GetNetFlow
{
    map<string, int> mp;

   public:
    GetNetFlowSt(int n_) : GetNetFlow(n_) {}
    void addEdge(string from, string to, int capacity)
    {
        if (!mp.count(from))
        {
            mp[from] = mp.size();
        }
        if (!mp.count(to))
        {
            mp[to] = mp.size();
        }
        while (mp.size() > n - 2)
        {
            graph.push_back(vector<shared_ptr<MSEdge>>());
            n++;
        }
        return GetNetFlow::addEdge(mp[from], mp[to], capacity);
    }

    long long getMaxFlow(string s, string t)
    {
        return GetNetFlow::getMaxFlow(mp[s], mp[t]);
    }
};

const int MAXN = 400 + 6;
int main()
{
    std::ios::sync_with_stdio(false);
    // 给每个插头分配一个编号，然后把插头作为节点，转接器作为边变成一个图
    // 然后每个用电器和电源接进图里面
    // 最后 S T 接用电器和电源，网络流 get

    int T, ptBlank = 0;
    cin >> T;
    while (T--)
    {
        GetNetFlowSt gf(MAXN);
        int n;
        cin >> n;
        int cnting = 1;
        vector<string> powers;
        for (int i = 0; i < n; i++)
        {
            string st;
            cin >> st;
            cin.get();
            powers.push_back(st);
        }
        cin >> n;
        vector<string> devs;

        for (int i = 0; i < n; i++)
        {
            string name, plug;
            cin >> name;
            cin.get();
            cin >> plug;
            cin.get();
            devs.push_back(plug);
        }

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string from, to;
            cin >> from;
            cin.get();
            cin >> to;
            cin.get();
            gf.addEdge(from, to, INF);
        }

        string s = "$s_", t = "$t_";
        for (auto dev : devs)
        {
            gf.addEdge(s, dev, 1);
        }

        for (auto pow : powers)
        {
            gf.addEdge(pow, t, 1);
        }
        if (ptBlank)
        {
            cout << '\n';
        }
        ptBlank = T;
        cout << max(0ll, (long long)devs.size() - gf.getMaxFlow(s, t)) << "\n";
    }
    return 0;
}
