#include <iostream>
#include <algorithm>

using namespace std;

struct node
{
	int v,x;
}F[100001];

int main()
{
    int N;
    cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d%d", &F[i].v, &F[i].x);
    }
    int xan = 0;
    for(int i = 1; i <= N; ++i)
    {
        for(int j = i + 1; j <= N; ++j)
        {
            xan += max(F[i].v, F[j].v) * abs(F[i].x - F[j].x);
        }
    }
    cout << xan;
    return 0;
}
