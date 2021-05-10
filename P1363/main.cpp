//re????
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int MAXN = 2000 + 2,MAXM = 2000 + 2, ADDTION = 2;

int n,m;
//x line y row
int start_x,start_y;
bool OK =false;
struct Node
{
    bool visable;
    int x_before;
    int y_before;
    Node(){x_before = 0; y_before = 0; visable = false;}
    void ccc(){x_before = 0; y_before = 0; visable = false;}
};

Node gph[MAXN][MAXM];

//bool jurge_edge(int x, int y);
bool jurge_visable (int x, int y);
bool jurge_success (int x, int y);
bool walk (int towards, int & x,int & y);//write x y value

bool dfs(int x,int y)
{
    if(OK)
    {
        return true;
    }
    //cout<<"Now x,y = "<<x % n<<","<<y % m<<endl;
    Node & now = gph[x % n][y % m];
    now.x_before = x;
    now.y_before = y;
    for(int i = 0; i < 4; ++i)//walk
    {
        int xx = x,yy = y;
        if(!walk(i,xx,yy))
        {
            cout<<"Oh I AK IOI!!!\n";
            exit(0);
        }
        //cout<<"  At xx%n = "<<xx%n<<" yy%n = "<<yy%m<<endl;
        if(jurge_visable(xx,yy))
        {
            //cout<<"    Go to xx%n = "<<xx%n<<" yy%n = "<<yy%m<<endl;
            dfs(xx,yy);
        }
        else if(jurge_success(xx,yy))
        {
            //cout<<"    suc x,y "<<xx%n<<" "<<yy%m<<endl;
            OK = true;
            return true;
        }
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    while(cin>>n>>m)
    {
        OK =false;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                char ch;
                cin>>ch;
                switch (ch)
                {
                case 'S':
                    {
                        start_x = i + ADDTION*n;
                        start_y = j + ADDTION*m;
                        //cout<<"Start x = "<<start_x % n<<" Satrt y = "<<start_y % m<<"i = "<<i<<" j = "<<j<<"\n\n";
                        gph[i][j].visable = true;
                    }break;
                case '.':
                    {
                        gph[i][j].visable = true;
                    }break;
                case '#':
                    {
                        gph[i][j].visable = false;
                    }break;
                default:
                    {
                        cout<<"AKIOI!!!!!\n";
                        exit(0);
                    }
                }
            }
        }

        /*queue<pair<int,int> > BFSQ;
        bool suc = false;
        Node & aaaa = gph[start_x % n][start_y % m];
        aaaa.x_before = start_x;
        aaaa.y_before = start_y;
        BFSQ.push( make_pair(start_x,start_y) );
        //cout<<"Start x = "<<start_x % n<<" Satrt y = "<<start_y % m<<"\n\n";
        while(!BFSQ.empty())
        {
            int tmp_x = BFSQ.front().first;
            int tmp_y = BFSQ.front().second;
            BFSQ.pop();

            cout<<"Now x,y = "<<tmp_x % n<<","<<tmp_y % m<<endl;
            for(int i = 0; i < 4; ++i)//walk
            {
                int xx = tmp_x,yy = tmp_y;
                if(!walk(i,xx,yy))
                {
                    cout<<"Oh I AK IOI!!!\n";
                    exit(1);
                }
                cout<<"  At xx%n = "<<xx%n<<" yy%n = "<<yy%m<<endl;
                if(jurge_visable(xx,yy))
                {
                    cout<<"    Pushed xx%n = "<<xx%n<<" yy%n = "<<yy%m<<endl;
                    Node & now = gph[xx % n][yy % m];
                    now.x_before = xx;
                    now.y_before = yy;
                    BFSQ.push(make_pair(xx,yy));
                }
                else if(jurge_success(xx,yy))
                {
                    suc = true;
                    cout<<"    suc x,y "<<xx%n<<" "<<yy%m<<endl;
                    break;
                }
            }
            if(suc)
            {
                break;
            }
        }*/
        dfs(start_x,start_y);

        if(OK)
        {
            cout<<"Yes\n";
        }
        else
        {
            cout<<"No\n";
        }
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                gph[i][j].ccc();
            }
        }

    }
    return 0;
}

/*bool jurge_edge(int x, int y)
{
    if(x > 0 && y > 0 && x <= n && y < m)
    {
        return true;
    }
    else
    {
        return false;
    }
}*/
bool jurge_visable (int x, int y)
{
    Node & tmp = gph[x % n][y % m];
    if(tmp.x_before == 0 && tmp.y_before == 0 && tmp.visable)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool jurge_success (int x, int y)
{
    Node & tmp = gph[x % n][y % m];
    if((tmp.x_before != x || tmp.y_before != y)&& tmp.visable&&!( x%n == start_x && y%m == start_y))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool walk (int towards,int& x,int& y)
{
    switch(towards)
    {
    case 0://up
        {
            x -= 1;

        }break;
    case 1://down
        {
            x += 1;
        }break;
    case 2://left
        {
            y -= 1;
        }break;
    case 3://right
        {
            y += 1;
        }break;
    default:
        {
            return false;
        }
    }
    return true;
}
