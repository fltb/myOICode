    #include <cstdio>
    #include <iostream>
    #include <cstdio>
    #include <vector>
    #include <stack>
    #include <algorithm>
    using std::cin;
    using std::cout;
    using std::vector;
    int max(int a, int b)
    {
        return a < b ? b : a;
    }
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
    template<typename T, int N>
    class Stack
    {
        T arr[N];
        int i;
    public:
        Stack():i(0) {}
        void push(const T & item)
        {
            arr[i++] = item;
        }
        const T & top()
        {
            return arr[i-1];
        }
        void pop()
        {
            i--;
        }
        int size()
        {
            return i;
        }
        bool empty()
        {
            return i <= 0;
        }
    };
    const int MAXN = 500000 + 5;

    char str[MAXN];
    int n, fa[MAXN];
    vector<int> graph[MAXN];

    Stack<int, MAXN> st;
    long long lst[MAXN], sum[MAXN];
    void dfs(int now);

    void dfs(int now)
    {
        int pre = 0;
        if (str[now] == ')' && !st.empty())
        {
            pre = st.top();
            st.pop();
            lst[now] = lst[fa[pre]] + 1;
        }
        else if (str[now] == '(')
        {
            st.push(now);
        }

        sum[now] = sum[fa[now]] + lst[now];

        for (auto it = graph[now].begin(); it != graph[now].end(); ++it)
        {
            int to = *it;
            dfs(to);
        }

        if (pre)
        {
            st.push(pre);
        }
        else if (!st.empty())
        {
            st.pop();
        }
    }

    int main()
    {
        std::ios::sync_with_stdio(false);
        cin >> n;
        cin.get();
        cin.getline(str+1, MAXN);

        for (int i = 2; i <= n ; i++)
        {
            int fa;
            cin >> fa;
            ::fa[i] = fa;
            graph[fa].push_back(i);
        }

        dfs(1);

        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans = (ans ^ (sum[i] * i));
        }
        cout << ans << '\n';
        return 0;
    }