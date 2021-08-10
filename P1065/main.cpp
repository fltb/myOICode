#include <iostream>
using std::cin;
using std::cout;
using std::endl;

const int MAXN = 20+5,
          MAXZ = 20*20+5;

int n, m,
    tasks[MAXN*MAXN],
    counts[MAXN][2], // counts[n][0] = num, counts[n][1] = time
    products_machine[MAXN][MAXN],
    costs[MAXN][MAXN],
    machines_left_point[MAXN][MAXZ],
    machines_right_point[MAXN][MAXZ];
    //for machines the machines_xxx_point[n_of_machine][0] = length of lists
    //and the machines_xxx_point[n][1] = 1

int max(int a, int b)
{
    return a < b ? b : a;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void init()
{
    for (int i = 1; i <= m; ++i)
    {
        machines_left_point[i][0] = 1;
        machines_right_point[i][0] = 1;
    }
}

int check(int machine, int start, int length)
{
    int mark = max(start, machines_right_point[machine][machines_right_point[machine][0]]);
    // the last r
    for (int i = 1; i < machines_right_point[machine][0]; ++i)
    {
        if (machines_left_point[machine][i+1] - start >= length && machines_left_point[machine][i+1] - machines_right_point[machine][i] >= length)
        {
            mark = max(start, machines_right_point[machine][i]);
            break;
        }
    }
    return mark;
}

void insert(int machine, int start, int length)
{
    ++machines_left_point[machine][0];
    ++machines_right_point[machine][0];
    for (int i = machines_left_point[machine][0]; i >=  2; --i)
    {
        if (start >= machines_right_point[machine][i-1])
        {
            machines_left_point[machine][i] = start;
            machines_right_point[machine][i] = start + length;
            break;
        }
        machines_left_point[machine][i] = machines_left_point[machine][i-1];
        machines_right_point[machine][i] = machines_right_point[machine][i-1];
    }
}

int get_ans()
{
    int ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int last = machines_right_point[i][0];
        ans = max(ans, machines_right_point[i][last]);
    }
    return ans;
}

int main()
{
    cin >> m >> n;

    for (int i = 1; i <= m*n; ++i)
    {
        cin >> tasks[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> products_machine[i][j];
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> costs[i][j];
        }
    }

    init();

    for (int i = 1; i <= n*m; ++i)
    {
        int num = tasks[i];
        int machine = products_machine[num][ ++counts[num][0] ],
            time_now = counts[num][1],
            length = costs[num][ counts[num][0] ];

        int start_time = check(machine, time_now, length);
        counts[num][1] = start_time + length;
        insert(machine, start_time, length);
    }
    cout << get_ans() << endl;
}
