#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::priority_queue;
const int MAXN = 1e5 + 2,
          INF = 2147483647;

int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a < b ? b : a;
}

struct Plane {
    int begin;
    int end;
    Plane(){}
    Plane(int b, int e) : begin(b), end(e) {}
    bool operator<(const Plane & x) const{
        if (begin < x.begin) {
            return true;
        } else if (begin == x.begin && end < x.end) {
            return true;
        } else {
            return false;
        }
    }
};

struct SmallPlane {
    Plane plane;
    int cur;
    SmallPlane(){};
    SmallPlane(const Plane & x, int c) : plane(x), cur(c) {}
    bool operator<(const SmallPlane & x) const {
        return !(plane.end < x.plane.end);
    }
};

int n, m1, m2,
    cnt_local[MAXN], cnt_foreign[MAXN]; // [] is the num of n


struct MyStruct {
    bool curs[MAXN];
    int min_cur = 1;
    MyStruct() {
        for (int i = 0; i < MAXN; ++i) {
            curs[i] = false;
        }
    }
    void insert(int x) {
        curs[x] = true;
        if (x == min_cur) {
            while (curs[min_cur]) {
                ++min_cur;
            }
        }
    }
    void pop(int x) {
        curs[x] = false;
        if (x < min_cur) {
            min_cur = x;
        }
    }
    int get_min() {
        return min_cur;
    }
};

/*
struct MyStruct {
    priority_queue<int, vector<int>, std::greater<int> > curs;
    void insert(int x) {
        curs.pop();
    }
    void pop(int x){
        curs.push(x);
    }
    int get_min() {
        return curs.top();
    }
};
*/
bool cmp_big_plane(const Plane & a, const Plane & b) {
    return !(a < b);
}

Plane local[MAXN], foreign[MAXN];
MyStruct ms_local, ms_foreign;

int main() {
#ifdef LOCAL
    freopen("myself.in", "r", stdin);
    freopen("myself.out","w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    cin >> n >> m1 >> m2;
    for (int i = 0; i < m1; ++i) {
        cin >> local[i].begin >> local[i].end;
    }
    for (int i = 0; i < m2; ++i) {
        cin >> foreign[i].begin >> foreign[i].end;
    }

    std::sort(local, local + m1);
    std::sort(foreign, foreign + m2);

    /*for (int i = 1; i <= n; ++i) {
        ms_local.curs.push(i);
        ms_foreign.curs.push(i);
    }*/

    // sum local
    priority_queue<SmallPlane> p_local;
    for (int i = 0; i < m1; ++i) {
        const Plane & now = local[i];
        if (!p_local.size()) {
            ++cnt_local[1];
            p_local.push(SmallPlane(now, 1));
            ms_local.insert(1);
            continue;
        }

        Plane top = p_local.top().plane;
        int cur = p_local.top().cur;
        while (p_local.size() && top.end < now.begin) {
            p_local.pop();
            ms_local.pop(cur);
            top = p_local.top().plane;
            cur = p_local.top().cur;
        }
        ++cnt_local[ms_local.get_min()];
        p_local.push(SmallPlane(now, ms_local.get_min()));
        ms_local.insert(ms_local.get_min());
    }

    // sum foreign
    priority_queue<SmallPlane> p_foreign;
    for (int i = 0; i < m2; ++i) {
        const Plane & now = foreign[i];
        if (!p_foreign.size()) {
            ++cnt_foreign[1];
            p_foreign.push(SmallPlane(now, 1));
            ms_foreign.insert(1);
            continue;
        }

        Plane top = p_foreign.top().plane;
        int cur = p_foreign.top().cur;
        while (p_foreign.size() && top.end < now.begin) {
            p_foreign.pop();
            ms_foreign.pop(cur);
            top = p_foreign.top().plane;
            cur = p_foreign.top().cur;
        }
        ++cnt_foreign[ms_foreign.get_min()];
        p_foreign.push(SmallPlane(now, ms_foreign.get_min()));
        ms_foreign.insert(ms_foreign.get_min());
    }

    // get ans
    for (int i = 1; i <= n; ++i) {
        cnt_local[i] += cnt_local[i-1];
        cnt_foreign[i] += cnt_foreign[i-1];
    }
    int ans = 0;
#ifdef LOCAL
    int ans_cur = 0;
#endif
    for (int k = 0; k <= n; ++k) {
        if (ans < cnt_local[k] + cnt_foreign[n-k]) {
            ans = cnt_local[k] + cnt_foreign[n-k];
#ifdef LOCAL
            ans_cur = k;
#endif
        }  
    }
    cout << ans << endl;
#ifdef LOCAL
    cout << ans_cur << " " << cnt_local[ans_cur] << " " << cnt_foreign[n-ans_cur];
    cout << endl << endl;
    for (int k = 0; k <= n; ++k) {
        cout << "k = " << k << " local = " << cnt_local[k] << "foreign = " << cnt_foreign[n-k] << endl;
    }
#endif
    return 0;
}