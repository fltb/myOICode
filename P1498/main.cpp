#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
char Mp[1030][2050];

void DfsPrint (int Line, int Row, int Deep)
{
    if(Deep == 1)
    {
        Mp[Line][Row    ]     = '/';
        Mp[Line][Row + 1]     = '\\';
        Mp[Line + 1][Row - 1] = '/';
        Mp[Line + 1][Row    ] = '_';
        Mp[Line + 1][Row + 1] = '_';
        Mp[Line + 1][Row + 2] = '\\';
        return;
    }
    //cout<< Line << " " << Row << " "<< Deep <<"\n";
    int Tmp = pow(2, Deep - 1);
    DfsPrint(Line, Row, Deep - 1);
    DfsPrint(Line + Tmp, Row - Tmp, Deep - 1);
    DfsPrint(Line + Tmp, Row + Tmp, Deep - 1);
}
int main()
{
    int N;
    cin >> N;
    for(int i = 1;i <= pow(2, N); i++)
    {
        strset(Mp[i], ' ');
    }
    DfsPrint(1, pow(2, N), N);
    for(int i = 1; i <= pow(2, N); ++i)
    {
        for(int j = 1; j <= pow(2, N + 1); ++j)
        {
            putchar(Mp[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
