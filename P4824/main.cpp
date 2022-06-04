#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::getline;
using std::stack;
using std::string;
using std::vector;
template <typename T>
inline void read(T &t)
{
    int f = 0, c = std::getchar();
    t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f)
        t = -t;
}
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

int main()
{
    std::ios::sync_with_stdio(false);
    string sInput, sBase;
    getline(cin, sInput);
    getline(cin, sBase);

    vector<size_t> kmp(sBase.length() + 1, -1);
    int k = -1;
    for (auto i = 1; i < sBase.length(); i++)
    {
        while (k > -1 & sBase[k + 1] != sBase[i])
        {
            k = kmp[k];
        }
        if (sBase[k + 1] == sBase[i])
        {
            k++;
        }
        kmp[i] = k;
    }

    // 使用一个栈来存当前对应的 kmp 值，这样就可以在弹出之后继续接上
    struct NodeJS
    {
        size_t i, k;
        NodeJS(size_t i_, size_t k_) : i(i_), k(k_) {}
    };
    stack<NodeJS> stck;
    for (auto i = 0; i < sInput.length(); i++)
    {
        auto k = -1;
        if (!stck.empty())
        {
            k = stck.top().k;
        }

        while (k > -1 && sInput[i] != sBase[k + 1])
        {
            k = kmp[k];
        }
        if (sInput[i] == sBase[k + 1])
        {
            k++;
        }
        stck.push(NodeJS(i, k));
        if (k + 1 == sBase.length())
        {
            for (int j = 0; j < sBase.length(); j++)
            {
                stck.pop();
            }
        }
    }

    stack<size_t> ansStack;
    while (!stck.empty())
    {
        auto i = stck.top().i;
        stck.pop();
        ansStack.push(i);
    }

    while (!ansStack.empty())
    {
        cout << sInput[ansStack.top()];
        ansStack.pop();
    }

    cout << '\n';
    return 0;
}