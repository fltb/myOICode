#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
    int n;
    vector<int> a;

    while (cin >> n)
    {
        a.clear();
        while (n--)
        {
            int now;
            cin >> now;
            a.push_back(now);
        }
        
    }

}