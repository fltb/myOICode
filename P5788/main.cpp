#include <ios>
#include <iostream>
#include <vector>
#include <stack>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    std::vector<int> arr(n + 1), ans(n + 1);
    std::stack<int> st;
    
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }

    for (int i = n; i >= 1; --i)
    {
        while (!st.empty() && arr[i] >= arr[st.top()])
        {
            st.pop();
        }

        if (st.empty())
        {
            ans[i] = 0;
        }
        else
        {
            ans[i] = st.top();
        }
        st.push(i);
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}