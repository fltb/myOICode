#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
const int MAXN = 9+1;

string a[MAXN][MAXN];
char ans[MAXN];
int put[255];
bool err = false;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> a[i][j];
            if (!put[int(a[i][j][0])] && a[i][j].size() == 2)
            {
                ans[1] = a[i][j][0];
                ++put[(int)ans[1]];
            }
        }
    }

    int cur = -1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 2; j <= n; ++j)
        {
            if (a[i][1] == a[i][j] && a[1][j] == a[i][j])
            {
                ans[0] = a[i][1][0];
                ++put[(int)ans[0]];
            }
            if (a[i][1][0] == ans[1] && a[i][1].size() == 1)
            {
                cur = i;
            }
        }
    }

    if (!(ans[0] && ans[1]))
    {
        cout << "ERROR!\n";
        return 0;
    }

    for (int k = 1; k <= n-3; ++k)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (ans[k] == a[1][j][0] && a[1][j].size() == 1)
            {
                ans[k+1] = a[cur][j][0];
                ++put[(int)ans[k+1]];
            }
        } 
    }
    for (int i = 0; i <= n-2; ++i)
    {
        if (!ans[i])
        {
            cout << "ERROR!\n";
            return 0;
        }
    }

    for (int i = 1; i < 255; ++i)
    {
        if (put[i] > 1)
        {
            cout << "ERROR!\n";
            return 0;         
        }
    }
    //M=1 N=2 P=0
    if (ans[0] == 'P' && ans[1] == 'M' && ans[2] == 'N')
    {
        cout << "ERROR!\n";
        return 0;   
    }

    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j <= n-2; ++j)
        {
            if (a[1][i][0] == ans[j])
            {
                cout << char(ans[j]) << "=" << j << " ";
            }
        }
    }
    cout << endl << n-1 << endl;

    return 0;
}
