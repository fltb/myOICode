#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#define cosnt const
using std::cin;
using std::cout;
using std::priority_queue;
using std::string;
using std::unordered_map;
using std::vector;
template <typename T>
inline void read(T& t) {
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}
/*
重新推导一遍吧，有点乱了
既然是图论，肯定是最短路的模板改改

对于当前点，我们考虑走某一条边，当 val =
    正点的概率 * 正点之后，另一边到终点的期望 +
    晚点的概率 * (
        晚了 1 的概率*  晚了 1 之后到达的节点到终点的期望
        + 晚了 2 的概率 * ...
        ......
        + 晚了 d 的概率 * 晚了 d 之后到达的节点到终点的期望
    )
算出来的 val 最小，这个 val 相当最短路里面的距离

由于计算当中，到达一个点的时间也是重要的一个变量，所以我们定义一个结点的距离值为
    (编号，到达时刻)
就是数组
    dis[MAXN][MAXS]

ERR！！！在最短路当中，不能把不同时间的站点作为一个独立的节点，节点就只有站点，不同时间要手动枚举，不然不好更新

主要过程
    fill dis[t][0...59] with 0
    while q:
        now = q.top if not vis now
        for (e : now):
            for startTime: 正点
                to = e(now)
                val = 当前正点的期望 * (长度 + d[now][reachT] )
                // 晚到达的
                for (s : duation): // 对面的发车时间
                    val += 这个点的期望 / 总期望 * (时间长度 + d[now][reachT])
                if val < dis[to] ans not inq:
                    push to into q

最终答案 min(dis[s][0...59])
*/
struct Edge {
    int u, v, departureTime, standardJourneyTime, maximumDelay;
    double probabilityOfDelays;
    Edge(int uu, int vv, int mm, int tt, double pp, int dd) : u(uu), v(vv), departureTime(mm), standardJourneyTime(tt), probabilityOfDelays(pp / 100), maximumDelay(dd) {}
    int to(int x) { return x == u ? v : u; }
};
const int MAXN = 2000 + 2, MAXS = 60;
const double INFD = 1e12 + 5;
int n;
unordered_map<string, int> mp;
unordered_map<int, string> mpBack;
int cnt;
double dis[MAXN][MAXS];  // 节点编号，几点到 = 期望时间
bool inq[MAXN];
vector<Edge> es;
vector<vector<int>> oppoG;
void initBeforeN() {
    cnt = 0;
    mp.clear();
    mpBack.clear();
    oppoG = vector<vector<int>>(MAXN, vector<int>());
    for (auto i = 0; i < MAXN; i++) {
        inq[i] = false;
        for (auto j = 0; j < MAXS; j++) {
            dis[i][j] = INFD;
        }
    }
    es.clear();
}

int addMp(const string& st) {
    if (!mp.count(st)) {
        mp[st] = ++cnt;
        mpBack[cnt] = st;
    }
    return mp[st];
}
int genTime(int now, int lasting) {
    return (now + lasting + MAXS * 100) % MAXS;
}
int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin.get();
        initBeforeN();
        string startSt, endSt;
        cin >> startSt >> endSt;
        auto s = addMp(startSt), t = addMp(endSt);
        cin >> n;
        cin.get();
        for (auto i = 1; i <= n; i++) {
            string s1, s2;
            int m, t, p, d;
            cin >> s1 >> s2 >> m >> t >> p >> d;
            int u = addMp(s1), v = addMp(s2);
            es.push_back(Edge(u, v, m, t, p, d));
            oppoG[v].push_back(es.size() - 1);
        }
        for (int tme = 0; tme < MAXS; tme++) {
            dis[t][tme] = 0.0;
        }
        std::queue<int> q;
        q.push(t);
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            inq[now] = false;
            for (auto ei : oppoG[now]) {
                bool pushable = false;
                auto& e = es[ei];
                auto from = e.to(now);
                for (auto startTime = 0; startTime < MAXS; startTime++) {
                    auto waitTime = genTime(e.departureTime, -startTime);
                    auto reachTime = genTime(e.departureTime, e.standardJourneyTime);
                    auto journeyTime = e.standardJourneyTime + dis[now][reachTime];
                    auto val = (double)waitTime;
                    val += (1 - e.probabilityOfDelays) * journeyTime;
                    for (auto delay = 1; delay <= e.maximumDelay; delay++) {
                        auto reachTime = genTime(e.departureTime, e.standardJourneyTime + delay);
                        auto journeyTime = e.standardJourneyTime + delay + dis[now][reachTime];
                        val += e.probabilityOfDelays * ((double)1 / e.maximumDelay) * journeyTime;
                    }
                    pushable = pushable || val < dis[from][startTime];
                    dis[from][startTime] = min(dis[from][startTime], val);
                }
                if (pushable & !inq[from]) {
                    q.push(from);
                }
            }
        }
        auto ans = INFD;
        for (int startTime = 0; startTime < MAXS; startTime++) {
            ans = min(ans, dis[s][startTime]);
        }
        if (ans == INFD) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << std::setprecision(10) << ans << '\n';
        }
    }
    return 0;
}