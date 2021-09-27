#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int main()
{
    int n,c,ans = 0;
    cin>>n>>c;
    long *a = new long[n];
    for(int i = 0; i < n ;i++)
        cin>>a[i];
    sort(a,a+n);
    for(int i = 0; i < n; i++)
    {
        ans+=((upper_bound(a,a+n,a[i]+c)-a)-(lower_bound(a,a+n,a[i]+c)-a));
    }
    cout<<ans;
    return 0;
}
