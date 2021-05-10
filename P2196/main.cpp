

/*////////////假装另一个文件////////////////////

class Node
{
private:
    int num;
    vector<int> connt;
public:
    Node(){  num = 0;}

    bool push (int x){  connt.push_back(x);   return true;}
    int connt_len () {   return connt.size();}
    int get_nx(int x){ return connt[x]; }

    bool set_num (int x){   num = x;    return true;}
    int  get_num () { return num;}

    friend istream & operator>> (istream & is,Node & it);
};


istream & operator>> (istream & is,Node & it)
{
    is>>it.num;
    return is;
}
/////////////////////////////////////////////

const int maxn = 20 + 1;
int n,
    ans [maxn],
    vised [maxn][maxn],
    maxa = 0;

Node cellar[maxn];

int dfs (int nx, int deep);

int main()
{
    for( int i = 1;i <=n ;i++)
        cellar[0].push(i);
    cin>>n;
    for(int i = 1;i <= n; i++)
        cin>>cellar[i];
    for(int i = 1;i <= n; i++)
    {
        for(int j = i + 1; j <= n; j++)
        {
            int k;
            cin>>k;
            if(k != 0)
                cellar[i].push(j);
        }
    }
    int aaa = dfs(0,0);
    int aaa = 0;
    for( int i = 0; i < cellar[0].connt_len(); i++)
    {
        int nxt = cellar[0].get_nx(i);
        int now = dfs(nxt,1);
        if(aaa < now)
        {
            aaa = now;
            ans [1] = nxt;
        }
    }
    for(int i = 1;i <= n;i++)
        cout<<cellar[i].get_num()<<" ";
    cout<<endl<<aaa;
    return 0;
}

int dfs(int nx, int deep)
{
    if(vised[nx][deep] != 0)
        return vised[nx][deep];

    int aaa = 0;
    for( int i = 0; i < cellar[nx].connt_len(); i++)
    {
        int nxt = cellar[nx].get_nx(i);
        vised[nxt][deep + 1] = dfs( nxt ,deep + 1);
        if(aaa < vised[nxt][deep + 1])
        {
            aaa = vised[nxt][deep + 1];
            ans [deep + 1] = nxt;
        }
    }
    vised[nx][deep] = aaa + cellar[nx].get_num();
    return vised[nx][deep];
}


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vet,
                 ans,
                 syms;
    int n;
    while(cin>>n)
    {
        vet.push_back(n);
    }
    n = 0;//now n is the number of the system
    for(vector<int>::iterator it = vet.begin(); it != vet.end(); ++it)
    {
        if( ans.empty() || ans.back() >= *it)
        {
            ans.push_back(*it);
        }
        else
        {
            vector<int>::iterator ii = upper_bound(ans.begin(),ans.end(),*it,greater<int>());
            *ii = *it;
        }
        if( syms.empty() || syms.back() < *it)
        {
            syms.push_back(*it);
        }
        else
        {
            vector<int>::iterator iii = lower_bound(syms.begin(),syms.end(),*it);
            *iii = *it;
        }
    }
    cout<<ans.size()<<endl<<syms.size()<<endl;
}

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;

    cin>>n;
    vector<int> permp(n+1),
                 ans;
    for(int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d",&tmp);
        permp[tmp] = i;
    }
    for(int i = 0; i < n; i++)
    {
        int it;
        scanf("%d",&it);
        if(ans.empty() || ans.back() <= permp[it])
        {
            ans.push_back(permp[it]);
        }
        else
        {
            *upper_bound(ans.begin(),ans.end(), permp[it]) = permp[it];
        }
    }
    cout<<ans.size();
}
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class baseJRC
{
    int num;
public:
    int& get_num(){return num;}
    void set_num(int x){num = x;}
};
class JRC : public baseJRC
{
    int aaa;
public:
    void aa(int x){aaa = x;}
    int get(){return aaa;}
};
int main()
{
    return 0;
}
