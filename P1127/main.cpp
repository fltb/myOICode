#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int maxn = 1000+1;
int n,dfs_vised[maxn],suc = 0;

vector<string> Words;
vector<int> FirstLetter[26];
vector<int> LastLetter[26];
vector<int> Edge[maxn];
vector<int> Answer;

int get_alpha_num (const char ch) {return ch - 'a';}

void dfs (int x)
{
    if(Answer.size() == n && suc == 0)
    {
        suc = 1;
        cout<<Words[Answer[0]];
        for(int i = 1; i < n;++i)
        {
            cout<<"."<<Words[Answer[i]];
        }
        cout<<endl;
    }
    if(suc == 0)
    {
        for(int i = 0;i < Edge[x].size(); ++i)
        {
            const int v = Edge[x][i];
            if(dfs_vised[x] != 1 && x != v)
            {
                dfs_vised[x] = 1;
                Answer.push_back(v);

                dfs(v);

                Answer.pop_back();
                dfs_vised[x] = 0;
                //cout<<Words[v]<<endl;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 0; i < n ; ++i)
    {
        string tmp;
        cin>>tmp;
        Words.push_back(tmp);
    }
    sort(Words.begin(),Words.end());
    for(int i = 0; i < n ; ++i)
    {
        const string & tmp = Words[i];
        const int TF = get_alpha_num(tmp.front()),
                   TL = get_alpha_num(tmp.back());

        FirstLetter[TF].push_back(i);
        LastLetter [TL].push_back(i);
    }
    /*
    int * BfsVised = new int[n];
    queue<int> BFS;
    BFS.push(0);
    while(!BFS.empty())
    {
        int x = BFS.front(); BFS.pop();
        vector<int> & FLT = FirstLetter[get_alpha_num(Words[x].back() )];
        vector<int> & LLT = LastLetter [get_alpha_num(Words[x].front())];
        for(int i = 0;i < FLT.size(); ++i)
        {
            const int v = FLT[i];
            if(!BfsVised[v])
            {
                BfsVised[v] = 1;
                BFS.push(v);
            }
        }
        for(int i = 0;i < LLT.size(); ++i)
        {
            const int v = LLT[i];
            if(!BfsVised[v])
            {
                BfsVised[v] = 1;
                BFS.push(v);
            }
        }
    }
    for(int i = 0;i < n; ++i)
    {
        if(!BfsVised[i])
        {
            cout<<"***\n";
            return 0;
        }
    }
    delete [] BfsVised;*/
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && Words[i].back() == Words[j].front())
                Edge[i].push_back(j);
    int sum = 0;
    for(int i = 0;i < n; ++i)
    {
        vector<int> & FLT = FirstLetter[get_alpha_num(Words[i].front() )];
        vector<int> & LLT = LastLetter [get_alpha_num(Words[i].front())];
        int degree = FLT.size() - LLT.size();
        //cout<<"Words["<<Words[i]<<"],i = "<<i<<",degree = "<<degree<<endl;
        if(degree == 1)
        {
            sum = i;
            break;
        }
    }
    //cout<<"Words["<<Words[sum]<<"],i = "<<sum<<endl;
    Answer.push_back(sum);
    dfs_vised[sum] = 1;
    dfs(sum);

    if(suc == 0)
    {
        cout<<"***"<<endl;
    }

    return 0;
}
