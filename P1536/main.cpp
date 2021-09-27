/*
题目描述
某市调查城镇交通状况，得到现有城镇道路统计表。表中列出了每条道路直接连通的城镇。市政府 "村村通工程" 的目标是使全市任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要相互之间可达即可）。请你计算出最少还需要建设多少条道路？

输入格式
输入包含若干组测试测试数据，每组测试数据的第一行给出两个用空格隔开的正整数，分别是城镇数目 nn 和道路数目 mm ；随后的 mm 行对应 mm 条道路，每行给出一对用空格隔开的正整数，分别是该条道路直接相连的两个城镇的编号。简单起见，城镇从 11 到 nn 编号。

注意：两个城市间可以有多条道路相通。

输出格式
对于每组数据，对应一行一个整数。表示最少还需要建设的道路数目。

输入输出样例
输入 #1 复制
4 2
1 3
4 3
3 3
1 2
1 3
2 3
5 2
1 2
3 5
999 0
0
输出 #1 复制
1
0
2
998
说明/提示
数据规模与约定
对于 100\%100% 的数据，保证 1 \le n < 10001≤n<1000 。
*/

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
int lst[1000+5];

int fnd_fa(int x);
int main()
{

    int n,m;

    while(true)
    {

        cin>>n;
        if(n == 0)
            break;
        cin>>m;

        for(int i = 1; i <= n; i++)
            lst[i] = i;//set father as own

        for(int i = 1; i <= m; i++)
        {

            int tmp1,tmp2;
            cin>>tmp1>>tmp2;
            int n1 = fnd_fa(tmp1);
            int n2 = fnd_fa(tmp2);
            lst[n1] = n2;
        }

        int road = 0;

        for(int i = 1; i <= n; i++)
        {

            if(fnd_fa(i) == i)
            {
                road++;
            }
        }
        cout<< road  -1 <<endl;

    }
    return 0;
}
int fnd_fa (int x)
{
    if (x != lst[x])
        lst[x] = fnd_fa(lst[x]);
    return lst[x];
}
