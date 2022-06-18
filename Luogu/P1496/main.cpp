#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    int n;
    vector<long long> First,
                 Last;

    cin>>n;

    for(int i = 0;i < n; ++i)
    {
        long long tmp1,tmp2;
        cin>>tmp1>>tmp2;
        First.push_back(tmp1);
        Last.push_back (tmp2);
    }
    sort(First.begin(),First.end());
    sort(Last.begin() ,Last.end() );

    long long ans = Last[0] - First[0];
    for(int i = 1; i < n; ++i)
    {
        ans += Last[i] - First[i];
        if(First[i] < Last[i - 1])
        {
            ans -= Last[i - 1] - First[i];
        }
    }
    cout<<ans;
    return 0;
}
