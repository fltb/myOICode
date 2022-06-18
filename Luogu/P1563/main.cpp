/*
题目描述

小南有一套可爱的玩具小人, 它们各有不同的职业。

有一天, 这些玩具小人把小南的眼镜藏了起来。 小南发现玩具小人们围成了一个圈,它们有的面朝圈内,有的面朝圈外。如下图:

这时singersingersinger告诉小南一个谜題: “眼镜藏在我左数第3个玩具小人的右数第111个玩具小人的左数第222个玩具小人那里。 ”

小南发现, 这个谜题中玩具小人的朝向非常关键, 因为朝内和朝外的玩具小人的左右方向是相反的: 面朝圈内的玩具小人, 它的左边是顺时针方向, 右边是逆时针方向; 而面向圈外的玩具小人, 它的左边是逆时针方向, 右边是顺时针方向。

小南一边艰难地辨认着玩具小人, 一边数着:

singersingersinger朝内, 左数第333个是archerarcherarcher。

archerarcherarcher朝外,右数第111个是thinkerthinkerthinker。

thinkerthinkerthinker朝外, 左数第222个是writewritewriter。

所以眼镜藏在writerwriterwriter这里!

虽然成功找回了眼镜, 但小南并没有放心。 如果下次有更多的玩具小人藏他的眼镜, 或是谜題的长度更长, 他可能就无法找到眼镜了 。 所以小南希望你写程序帮他解决类似的谜題。 这样的谜題具体可以描述为:

有 nnn个玩具小人围成一圈, 已知它们的职业和朝向。现在第111个玩具小人告诉小南一个包含mmm条指令的谜題, 其中第 zzz条指令形如“左数/右数第s ss,个玩具小人”。 你需要输出依次数完这些指令后,到达的玩具小人的职业。
输入格式

输入的第一行包含两个正整数 n,mn,mn,m，表示玩具小人的个数和指令的条数。

接下来 nnn 行，每行包含一个整数和一个字符串，以逆时针为顺序给出每个玩具小人的朝向和职业。其中 000 表示朝向圈内，111 表示朝向圈外。 保证不会出现其他的数。字符串长度不超过 101010 且仅由小写字母构成，字符串不为空，并且字符串两两不同。整数和字符串之间用一个空格隔开。

接下来 mmm 行，其中第 iii 行包含两个整数 ai,sia_i,s_iai​,si​，表示第 iii 条指令。若 ai=0a_i=0ai​=0，表示向左数 sis_isi​ 个人；若 ai=1a_i=1ai​=1，表示向右数 sis_isi​ 个人。 保证 aia_iai​ 不会出现其他的数，1≤si<n1 \le s_i < n1≤si​<n。
输出格式

输出一个字符串，表示从第一个读入的小人开始，依次数完 mmm 条指令后到达的小人的职业。
输入输出样例
输入 #1

7 3
0 singer
0 reader
0 mengbier
1 thinker
1 archer
0 writer
1 mogician
0 3
1 1
0 2

输出 #1

writer

输入 #2

10 10
1 C
0 r
0 P
1 d
1 e
1 m
1 t
1 y
1 u
0 V
1 7
1 1
1 4
0 5
0 3
0 1
1 6
1 2
0 8
0 4

输出 #2

y

说明/提示

【样例1说明】

这组数据就是【题目描述】 中提到的例子。

【子任务】

子任务会给出部分测试数据的特点。 如果你在解决题目中遇到了困难, 可以尝试只解决一部分测试数据。

每个测试点的数据规模及特点如下表:

其中一些简写的列意义如下:

• 全朝内: 若为“√”, 表示该测试点保证所有的玩具小人都朝向圈内;

全左数:若为“√”,表示该测试点保证所有的指令都向左数,即对任意的

1≤z≤m,ai=01≤z≤m, a_i=01≤z≤m,ai​=0;

s=1s= 1s=1:若为“√”,表示该测试点保证所有的指令都只数1个,即对任意的

1≤z≤m,si=11≤z≤m,s_i=11≤z≤m,si​=1;

职业长度为111 :若为“√”,表示该测试点保证所有玩具小人的职业一定是一个

长度为111的字符串。

*/
#include <iostream>
#include <cstdio>
#include <string>
using std::cout;
using std::cin;
using std::endl;

const int MAXN = 100000+2;

struct Person
{
    int toward;
    std::string name;
}person[MAXN];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        cin >> person[i].toward >> person[i].name;
    }
    int cur = 0;
    for (int i = 0; i < m; ++i)
    {
        int a, s;
        scanf("%d%d", &a, &s);
        if(a == person[cur].toward) //顺时针
        {
            cur = (cur - s + n) % n;
        }
        else
        {
            cur = (cur + s + n) % n;
        }
    }
    cout << person[cur].name;
}
