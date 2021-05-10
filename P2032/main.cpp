#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;
int ArraySelf [2000001];
int main()
{
    int ArrayNumber = 0;
    int BlankK = 0;
    cin>>ArrayNumber>>BlankK;
    deque<int> BlaSelf;

    for(int i = 1; i <= ArrayNumber; ++i)
    {
        cin>>ArraySelf[i];

        while
        (!BlaSelf.empty() && ArraySelf[ BlaSelf.back() ] <ArraySelf[i] )
        {
            BlaSelf.pop_back();
        }
        if(!BlaSelf.empty() && i - BlaSelf.front() >= BlankK)
        {
            BlaSelf.pop_front();
        }
        BlaSelf.push_back(i);

        if(i >= BlankK )
        {
            cout<<ArraySelf[BlaSelf.front()]<<endl;
        }
    }
    return 0;
}
