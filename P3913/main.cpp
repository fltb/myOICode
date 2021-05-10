#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long  N,K;
    vector<long long> X,Y;
    cin>>N>>K;
    for(long long i = 0; i < K; ++i)
    {
        long long  tmpx,tmpy;
        cin>>tmpx>>tmpy;
        X.push_back(tmpx);
        Y.push_back(tmpy);
    }
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());
    long long SizeX = unique(X.begin(),X.end()) - X.begin();
    long long SizeY = unique(Y.begin(),Y.end()) - Y.begin();
    cout<<(SizeX*N + SizeY*N - SizeX*SizeY)<<endl;
    return 0;
}
