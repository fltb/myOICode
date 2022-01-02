#include <iostream>
#include <valarray>
#include <vector>
#include <string>
#include <queue>
using std::cin;
using std::cout;
using std::string;
const int MAXN = 1000000 + 1;

struct Node
{
    int son[26], val, fail;

    Node()
    {
        for (int i = 0; i < 26; ++i)
        {
            son[i] = 0;
        }
        val = 0;
        fail = 0;
    }
};

std::vector<Node> tree;

void insert(const string & str)
{
    int tc = 0; // root
    for (size_t i = 0; i < str.size(); i++)
    {
        int key = str[i] - 'a';
        if (tree[tc].son[key] == 0)
        {
            tree[tc].son[key] = tree.size();
            tree.push_back(Node());
        }
        tc = tree[tc].son[key];
    }
    tree[tc].val++;
}

void update_fail()
{
    std::queue<int> q;
    for (int i = 0; i < 26; ++i)
    {
        Node & now = tree[0];
        if (now.son[i] != 0)
        {
            Node & son = tree[now.son[i]];
            son.fail = 0;
            q.push(now.son[i]);
        }
    }

    while (!q.empty())
    {
        Node & now = tree[q.front()];
        q.pop();
        for (int i = 0; i < 26; ++i)
        {
            Node & fail = tree[now.fail];
            if (now.son[i])
            {
                Node & son = tree[now.son[i]];
                son.fail = fail.son[i];
                q.push(now.son[i]);
            }
            else
            {
                now.son[i] = fail.son[i];
            }
        }
    }
}

int query(const string & str)
{
    int u = 0, ans = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        int key = str[i] - 'a';
        u = tree[u].son[key];
        for (int v = u; v && tree[v].val != -1; v = tree[v].fail)
        {
            ans += tree[v].val;
            tree[v].val = -1;
        }
    }
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    tree.push_back(Node());
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string str;
        cin >> str;
        insert(str);
    }
    update_fail();
    string str;
    cin >> str;
    cout << query(str) << "\n";
    return 0;
}
