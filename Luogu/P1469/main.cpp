#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n,x,ans =0;

    cin>>n;

    for(int i = 0; i < n; ++i)
    {
        cin>>x;
        ans^=x;
    }
    cout<<ans;
    return 0;
}
