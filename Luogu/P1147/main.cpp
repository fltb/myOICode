#include <iostream>

using namespace std;

int main()
{
    int m;
    cin>>m;
    for(int  i = 1; i <= m/2 ; ++i)
    {
        int aaa = 0;
        int j;
        for(j = i; j<m ; ++j)
        {
            aaa += j;
            if(aaa >= m)
            {
                break;
            }
        }

        if(aaa == m)
        {
            cout<<i<<" "<<j<<endl;
        }

    }
    return 0;
}
