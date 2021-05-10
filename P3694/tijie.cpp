#include<bits/stdc++.h>
using namespace std;
const int maxn = 21;
int f[1<<maxn];
int num[maxn];
int a[100005];
int sum[100005][maxn];
int n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        num[a[i]]++;//记录每个乐队的总人数
        for(int j=1;j<=m;++j)sum[i][j] = sum[i-1][j];//初始化sum数组
        sum[i][a[i]]++;//求每个乐队人数的前缀和
    }
    memset(f,0x3f,sizeof(f));//初始化最大值
    f[0] = 0;//一个乐队都没有的时候取0人
    for(int i=1;i<(1<<m);++i){
        int len = 0;
        for(int j=1;j<=m;++j)if(i & (1<<(j-1)))len += num[j];//如果当前状态下取了j乐队的人，总人数就加上j乐队的人数
        for(int j=1;j<=m;++j){
            if(i & (1<<(j-1)))//效率优化，当前状态取了他再进行取min，不然取min没有意义
                  f[i] = min(f[i],f[i ^ (1<<(j-1))] + num[j] - sum[len][j]+sum[len - num[j]][j]);//状态转移，取第j个乐队要加上该乐队人数，减去这一段中本来就有的该乐队人数
        }
    }
    int ans = f[(1<<m)-1];
    cout<<ans;
}
