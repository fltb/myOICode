#include <iostream>
#include <algorithm>
#include <cstring>
using std::cin;
using std::cout;
int max(int a, int b)
{
    return a < b ? b : a;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
const int MAXN = 500000 + 5,
          Green = 1;
struct NodeJS {
    int l, r;
    NodeJS(int lc=0, int rc=0) : l(lc), r(rc) {}
};

NodeJS tree[MAXN];
char str[MAXN];
int cntTree;

void buildTree(int root) {
    ++cntTree;
    char ch = str[root];
    switch (ch) {
        case '0':
            return;
            break;
        case '1':
            tree[root].l = root + 1;
            buildTree(root + 1);
            break;
        case '2':
            tree[root].l = root + 1;
            buildTree(root + 1);
            tree[root].r = cntTree + 1;
            buildTree(cntTree + 1);
            break;
    }
}

// dp[node][color]: 当前节点涂成当前颜色的时候，它的**子节点中**最(多|少)颜色 1 出现的次数
int recMax[MAXN][4];
int dfsMax(int node, int color) {
    int & recX = recMax[node][color];
    if (recX != -1) {
        return recX;
    }
    // 遍历子树，看是否能加上
    for (int i = 1; i <= 3; i++) {
        if (i == color) {
            continue;
        } // i != color
        // 可以走下去
        auto & now = tree[node];
        if (now.l) {
            int val = 0;
            int valL = dfsMax(now.l, i);
            val += valL;
            if (now.r) {
                for (int j = 1; j <= 3; j++) {
                    if (j == i || j == color) {
                        continue;
                    }
                    int add = int(j == Green || i == Green);
                    int valR = dfsMax(now.r, j);
                    val += valR + add;
                    recX = max(val, recX);
                    val -= valR + add;
                }
            } else {
                int add = int(i == Green);
                recX = max(recX, val + add);
            }
        }
    }
    #ifdef DEBUG
    cout << "Node: " << node << " Color: " << color << " recX: " << max(recX, 0) << "\n";
    #endif
    return recX = max(recX, 0);
}

int recMin[MAXN][4];
int dfsMin(int node, int color) {
    int & recX = recMin[node][color];
    if (recX < 0x3f3f3f3f - 10000) {
        return recX;
    }
    bool isLeaf = true;
    // 遍历子树，看是否能加上
    for (int i = 1; i <= 3; i++) {
        if (i == color) {
            continue;
        } // i != color
        // 可以走下去
        auto & now = tree[node];
        if (now.l) {
            isLeaf = false;
            int val = 0;
            int valL = dfsMin(now.l, i);
            val += valL;
            if (now.r) {
                for (int j = 1; j <= 3; j++) {
                    if (j == i || j == color) {
                        continue;
                    }
                    int add = int(j == Green || i == Green);
                    int valR = dfsMin(now.r, j);
                    val += valR + add;
                    recX = min(val, recX);
                    val -= valR + add;
                }
            } else {
                int add = int(i == Green);
                recX = min(recX, val + add);
            }
        }
    }
    #ifdef DEBUG
    cout << "NodeMIN: " << node << " Color: " << color << " recX: " << (isLeaf ? 0 : recX) << "\n";
    #endif
    return recX = isLeaf ? 0 : recX;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.getline(str+1, MAXN);

    buildTree(1);
    
    std::memset(recMax, -1, sizeof(recMax));
    std::memset(recMin, 0x3f, sizeof(recMin));
    int mx = -1, mn = 2147483647;
    for (int i = 1; i <= 3; i++) {
        int add = int(i == Green);
        mx = max(mx, dfsMax(1, i) + add);
    }

    for (int i = 1; i <= 3; i++) {
        int add = int(i == Green);
        mn = min(mn, dfsMin(1, i) + add);
    }

    cout << mx << " " << mn << "\n";
    return 0;
}
