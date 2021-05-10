#include <iostream>
#include <cmath>

using namespace std;
const int MAXM = 100 + 2,MaxT = 1000 + 2;
int w[MAXM],
    v[MAXM],
    ans[MaxT],
    m , t;

int main()
{
    cin>>t>>m;
    for(int i = 1; i <= m; ++i)
    {
        cin>>w[i]>>v[i];
    }
    for(int i = 1; i <= m; ++i)
    {
        for(int j = t;j >= w[i]; --j)
        {
            ans[j] = max(ans[j], ans[j - w[i]] + v[i]);
        }
    }
    cout<<ans[t];
    return 0;
}
