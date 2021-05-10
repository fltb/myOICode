#include <iostream>

using namespace std;
struct Node
{
    int left;
    int right;
    bool father;
    Node(){left = -1;right = -1;father = false;}
}tree[26 + 1];

istream & operator>>(istream & is, Node & nd)
{
    char ch[2];
    is>>ch[0]>>ch[1];
    if('*' != ch[0])
    {
        nd.left  = ch[0] - 'a';
        tree[ch[0] - 'a'].father = true;
    }
    if('*' != ch[1])
    {
        nd.right = ch[1] - 'a';
        tree[ch[1] - 'a'].father = true;
    }
    return is;
}
void dfs(int nd)
{
    cout.put(nd + 'a');
    if(tree[nd].left != -1)
    {
        dfs(tree[nd].left);
    }
    if(tree[nd].right != -1)
    {
        dfs(tree[nd].right);
    }
}
int main()
{
    int n;
    cin>>n;
    for(int i = 0;i < n; i++)
    {
        char ch;
        cin>>ch>>tree[ ch - 'a' ];
    }
    for(int i = 0;i < n; i++)
    {
        if(tree[i].father == false)
        {
            dfs(i);
            break;
        }
    }
    return 0;
}
