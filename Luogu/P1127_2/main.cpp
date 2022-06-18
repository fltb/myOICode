#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
const int maxn = 1000 + 2;

int n,dfs_visted[maxn],suc = 0;
vector<string> Words;
map<char,int> FirstLetter,LastLetter;
vector<int> NeWords[maxn];
vector<int> Answer;

void dfs (int x);
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 0;i < n; ++i)
    {
        string tmp;
        cin>>tmp;
        Words.push_back(tmp);
        FirstLetter[tmp.front()]++;
        LastLetter [tmp.back() ]++;
    }
    sort(Words.begin(),Words.end());
    for(int i = 0;i < n; ++i)
    {
        for(int j = 0;j < n; ++j)
        {
            if(i != j && Words[i].back() == Words[j].front())
            {
                NeWords[i].push_back(j);
                //cout<<"Word i = "<<Words[i]<<", Word j = "<<Words[j]<<endl;
            }
        }
    }
    int sum = 0;
    for(int i = 0; i < n; ++i)
    {
        if(FirstLetter[Words[i].front()] - LastLetter[Words[i].front()] == 1)
        {
            sum = i;
            break;
        }
    }

    //cout<<"FIND = "<<Words[sum]<<endl;
    dfs_visted[sum] = 1;
    Answer.push_back(sum);
    dfs(sum);

    if(suc == 0)
    {
        cout<<"***"<<endl;
    }

    return 0;
}

void dfs (int x)
{
    if(suc == 0 && Answer.size() == n)
    {
        suc = 1;
        for(int i = 0; i < n - 1; ++i)
        {
            cout<<Words[Answer[i]]<<".";
        }
        cout<<Words[Answer[n-1]]<<endl;
    }
    if(suc == 0)
    {
        for(int i = 0; i < NeWords[x].size(); ++i)
        {
            const int v = NeWords[x][i];
            if(dfs_visted[v] == 0)
            {
                dfs_visted[v] = 1;
                Answer.push_back(v);

                dfs(v);

                Answer.pop_back();
                dfs_visted[v] = 0;
            }
        }
    }
}
