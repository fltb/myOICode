#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::map;
using std::memset;
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

const int maxn = 400 + 6, maxm= 300 + 2;
struct Edge{
    long long int to, next, weight;
};
Edge edges[maxm]; 
long long int edge_cnt = 1, head[maxn];
int n = maxn, s, t;

void add(long long int x,long long  int y,long long int w){
    edges[++edge_cnt].next = head[x];
    edges[edge_cnt].to = y;
    edges[edge_cnt].weight = w;
    head[x] = edge_cnt;
}

long long int lasting[maxn], flow[maxn];
bool bfs(){
    std::memset(lasting, -1, sizeof(lasting));
    queue<int> q;
    q.push(s); 
    flow[s] = INF;
    while (!q.empty()){
        long long int front = q.front();
        q.pop();
        if (front == t) break;
        for (int eg = head[front]; eg != 0; eg = edges[eg].next){
            long long int v = edges[eg].to, vol = edges[eg].weight;
            if (lasting[v] == -1 && vol > 0){
                lasting[v] = eg;
                flow[v] = min(flow[front], vol);
                q.push(v);
            }
        }
    }
    return (lasting[t] != -1);
}

long long int EK(){
    long long int max_flow = 0;
    while(bfs()){
        for (int i = t; i != s; i = edges[lasting[i] ^ 1].to){
            edges[lasting[i]].weight -= flow[t];
            edges[lasting[i] ^ 1].weight += flow[t];
        }
        max_flow += flow[t];
    }
    return max_flow;
}
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
        int n;
        cin >> n;
        int cnting = 1;
        map<string, int> st2i;
        vector<int> powers;
#ifdef FLOATINGBLOCK
        auto prttt = [&st2i](string st)
        {
            cout << st << ": " << st2i[st] << '\n';
        };
#endif
        for (int i = 0; i < n; i++)
        {
            string st;
            cin >> st;
            cin.get();
            st2i[st] = cnting++;
#ifdef FLOATINGBLOCK
            prttt(st);
#endif
            powers.push_back(st2i[st]);
        }
        cin >> n;
        vector<int> devs;

        for (int i = 0; i < n; i++)
        {
            string name, plug;
            cin >> name;
            cin.get();
            cin >> plug;
            cin.get();
            st2i[name] = cnting++;
#ifdef FLOATINGBLOCK
            prttt(name);
#endif
            if (!st2i.count(plug))
            {
                st2i[plug] = cnting++;
#ifdef FLOATINGBLOCK
                prttt(plug);
#endif
            }
            add(st2i[name], st2i[plug], INF);

            devs.push_back(st2i[name]);
        }

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string from, to;
            cin >> from;
            cin.get();
            cin >> to;
            cin.get();
            if (!st2i.count(from))
            {
                st2i[from] = cnting++;
#ifdef FLOATINGBLOCK
                prttt(from);
#endif
            }
            if (!st2i.count(to))
            {
                st2i[to] = cnting++;
#ifdef FLOATINGBLOCK
                prttt(to);
#endif
            }
            add(st2i[from], st2i[to], INF);
        }

        int s = cnting++, t = cnting++;
        ::s = s, ::t = t;
        for (auto dev : devs)
        {
            add(s, dev, 1);
        }

        for (auto pow : powers)
        {
            add(pow, t, 1);
        }
        if (ptBlank)
        {
            cout << '\n';
        }
        ptBlank = T;
        cout << max(0ll, (long long)devs.size() -  EK()) << "\n";
    }
    return 0;
}