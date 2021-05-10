#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;
int a[ 10000000 + 2];
int main()
{
    int n,m;
    deque<int> DQ;
    cin>>n>>m;
    a[0] = 0;
    cout<<0<<endl;
    for(int i = 1; i < n; ++i)
    {
        scanf("%d",&a[i]);
        while(!DQ.empty() && a[i] < a[ DQ.back() ])
        {
            DQ.pop_back();
        }
        if(!DQ.empty() && i - DQ.front() >= m)
        {
            DQ.pop_front();
        }
        DQ.push_back(i);
        cout<<a[DQ.front()]<<endl;
    }
    return 0;
}
