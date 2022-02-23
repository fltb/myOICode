#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <iomanip>
using std::cin;
using std::cout;
using std::pair;
using std::queue;
const int MAXN = 50 + 3;
enum ACTIONS{
    Creep,
    Walk,
    Run,
    Left,
    Right
};

enum TOWARDS {
    ToEast,
    ToWest,
    ToNorth,
    ToSouth
};

int TotoTOWARDS [26];

struct PointAt {
    int x, y;
    int toward;
    PointAt(int xx = 0, int yy = 0, int ttoward = -1): x(xx), y(yy), toward(ttoward) {}
};

int mp[MAXN][MAXN],
    cost[MAXN][MAXN][5],
    vis[MAXN][MAXN],
    n, m;

PointAt movePoint(const PointAt & point, int steep) {
    PointAt endPoint = point;
    switch (point.toward) {
        case ToEast:
            endPoint.x = endPoint.x + steep;
            break;
        case ToWest:
            endPoint.x = endPoint.x - steep;
            break;
        case ToNorth:
            endPoint.y = endPoint.y - steep;
            break;
        case ToSouth:
            endPoint.y = endPoint.y + steep;
            break;
        default:
            throw "OMG WTF???";
    }
    return endPoint;
}

PointAt turnPoint(const PointAt & point, int to) {
    PointAt endPoint = point;
    if (to == Left) {
        switch (point.toward) {
            case ToEast:
                endPoint.toward = ToNorth;
                break;
            case ToWest:
                endPoint.toward = ToSouth;
                break;
            case ToNorth:
                endPoint.toward = ToWest;
                break;
            case ToSouth:
                endPoint.toward = ToEast;
                break;
            default:
                throw "OMG WTF???";
        }
    } else {
        switch (point.toward) {
            case ToEast:
                endPoint.toward = ToSouth;
                break;
            case ToWest:
                endPoint.toward = ToNorth;
                break;
            case ToNorth:
                endPoint.toward = ToEast;
                break;
            case ToSouth:
                endPoint.toward = ToWest;
                break;
            default:
                throw "OMG WTF???";
        }
    }
    return endPoint;
}

bool walkAble(const PointAt & point, int steep) {
    PointAt endPoint;
    for (int i = 1; i <= steep; i++) {
        endPoint = movePoint(point, i);
        if (mp[endPoint.x][endPoint.y]) {
            return false;
        }
    }
    return true;
}


/**
 *@{returns<PointAt, bool>} - if walkable
 */
pair<PointAt, bool> walk(const PointAt & point, int mode) {
    PointAt endPoint = point;
    bool walkAbleAAA = true;
    switch (mode) {
        case Creep:
            walkAbleAAA = walkAble(point, 1);
            endPoint = movePoint(endPoint, 1);
            break;
        case Walk:
            walkAbleAAA = walkAble(point, 2);
            endPoint = movePoint(endPoint, 2);
            break;
        case Run:
            walkAbleAAA = walkAble(point, 3);
            endPoint = movePoint(endPoint, 3);
            break;
        case Left:
            endPoint = turnPoint(endPoint, Left);
            break;
        case Right:
            endPoint = turnPoint(endPoint, Right);
            break;
        default:
            throw "OMG WTF**C*F???";
    }
    return std::make_pair(endPoint, walkAbleAAA);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= m; x++) {
            int val;
            cin >> val;
            if (val) {
                mp[x][y-1] = 1;
                mp[x][y] = 1;
                mp[x-1][y] = 1;
                mp[x-1][y-1] = 1;
            }
        }
    }

    for (int cur = 1; cur <= n; cur++) {
        mp[0][cur] = 1;
        mp[m][cur] = 1;
    }
    for (int cur = 1; cur <= m; cur++) {
        mp[cur][0] = 1;
        mp[cur][n] = 1;
    }

    std::memset(cost, 0x3f3f3f, sizeof(int)*MAXN*MAXN*5);

    TotoTOWARDS['W'-'A'] = ToWest;
    TotoTOWARDS['E'-'A'] = ToEast;
    TotoTOWARDS['S'-'A'] = ToSouth;
    TotoTOWARDS['N'-'A'] = ToNorth;

    PointAt startPoint, finalPoint;
    int x1, y1, x2, y2;
    char TTT;
    cin >> y1 >> x1 >> y2 >> x2;
    cin >> TTT;
    while (TTT == ' ') {
        cin >> TTT;
    }
    startPoint = PointAt(x1, y1, TotoTOWARDS[TTT - 'A']);
    finalPoint = PointAt(x2, y2);

    queue<PointAt> q;
    q.push(startPoint);
    cost[startPoint.x][startPoint.y][startPoint.toward] = 0;
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        auto x = now.x;
        auto y = now.y;
        auto toward = now.toward;
        vis[x][y] = true;
        for (int act = 0; act < 5; act++) {
            auto tmp = walk(now, act);
            auto success = tmp.second;
            if (success) {
                auto endPoint = tmp.first;
                auto xTo = endPoint.x;
                auto yTo = endPoint.y;
                auto towardTo = endPoint.toward;
                if (cost[x][y][toward] + 1 < cost[xTo][yTo][towardTo]) {
                    cost[xTo][yTo][towardTo] = cost[x][y][toward] + 1;
                    q.push(endPoint);
                }
            }
        }
    }

    int ans = 2147483647;
    for (int i = 0; i < 5; i++) {
        ans = std::min(cost[finalPoint.x][finalPoint.y][i], ans);
    }
    /*for (int i = 1; i < MAXN; i++) {
        for (int j = 1; j < MAXN; j++) {
            int aaa = 2147483647;
            for (int k = 0; k < 4; k++) {
                aaa = std::min(cost[j][i][k], aaa);
            }
            cout << std::setw(4) << ((aaa == 1061109567) ? 0 : aaa) << ", ";
        }
        cout << "\n";
    }*/
    if (vis[finalPoint.x][finalPoint.y]) {
        cout << ans;
    } else {
        cout << -1;
    }
    return 0;
}

