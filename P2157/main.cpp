#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <type_traits>
template <typename T> inline void read(T& t) {
    int f = 0, c = std::getchar(); t = 0;
    while (!std::isdigit(c)) f |= c == '-', c = std::getchar();
    while (std::isdigit(c)) t = t * 10 + c - 48, c = std::getchar();
    if (f) t = -t;
}
template<typename T> inline
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T> inline
T min(T a, T b)
{
    return a < b ? a : b;
}
class Student {
public:
    int v, b;
    Student(int v_=0, int b_=0) : v(v_), b(b_) {}
};
const int MAXN = 1000 + 2, MAX_STATE = (1 << 8), MAXB = 20, INF = 0x7fffffff;
/**
 * dp[第几个][当前的状态][插了几个人在前面]
 * 
 * 考虑转移中：
 */
int dp[MAXN][MAX_STATE][MAXB];
Student stu[MAXN];
void init()
{
    for (auto i = 0; i < MAXN; i++)
    {
        for (auto j = 0; j < MAX_STATE; j++)
        {
            for (auto k = 0; k < MAXB; k++)
            {
                dp[i][j][k] = INF;
            }
        }
        //stu[i] = Student();
    }
}

void update(int & dp1, const int & dp2)
{
    dp1 = min(dp1, dp2);
}

int getVal(const int cur, const int curNxt)
{
    // ERR: 忘了初始化的条件了
    if (cur == 0) {  return 0; }
    return stu[cur].v ^ stu[curNxt].v;
}

int dc(const int dis)
{
    return dis + 9;
}

int main()
{
    int cnt;
    read(cnt);            
    while(cnt--)
    {
        init();
        int n;
        read(n);
        
        for (auto i = 1; i <= n; i++)
        {
            Student & st = stu[i];
            read(st.v);
            read(st.b);
        }

        dp[1][0][dc(-1)] = 0;
        for (auto i = 1; i <= n; i++)
        {
            const auto & nowStu = stu[i];
            /*
                提取当前的状态，
                使用当前的状态更新后面可能遇到的值，试着用当前的人去更新后面，这样可以避免记录先前从哪里跳过来
                当前转移后面的时候，先考虑自己有没有被包含在吃饭了的人当中
                如果自己吃过，就可以直接向下更新了
                如果自己没有吃过，就要更新下面的 1...b 的人的状态，尝试让他们插到自己前面去
                    插到前面的时候，要考虑已经插队了的人是否会影响当前的最右边可以达到的值，所以记录

                现在，开始！
            */

            // ERR final: stNow <= MAX_STATE 导致了越界，所以出问题了
            for (auto stNow = 0; stNow < MAX_STATE; stNow++)
            {                
                for (auto pos = -8; pos <= 7; pos++)
                {
                    const auto dpNowVal = dp[i][stNow][dc(pos)];
                    if (dpNowVal == INF) // 当前不存在
                    {
                        continue;
                    }

                    if (stNow & 1) // 自己吃过了
                    {
                        // 那就直接更新后面的，是直接跳，没有转移走的，所以不用加上异或
                        update(dp[i+1][stNow>>1][dc(pos-1)], dpNowVal);
                    }
                    else // 那就是自己没吃过
                    {
                        // 先把当前的限制搞好, 限制是会更新的
                        auto limit = nowStu.b;
                        // 右边第几个插队
                        for (auto to = 0; to <= 7; to++)
                        {
                            // ERR 之前写成 to << 1 了，所以这次换 jump 变量
                            const auto jump = (1 << to);
                            if (jump & stNow) // 已经有了
                            {
                                continue;
                            }
                            if (to > limit) // 没有必要挣扎了
                            {
                                break;
                            }
                            const auto & nxtStu = stu[i + to];
                            update(limit, nxtStu.b + to);

                            const auto stNxt = stNow | jump;

                            // 这步是关键，需要更新异或的，从 dis 对应的跳到 to 对应的
                            update(dp[i][stNxt][dc(to)], dpNowVal + getVal(i + pos, i + to));
                        }
                    }
                }
            }
        }

        auto ans = INF;
        for (auto i = -8; i <= 0; i++)
        {
            // ERR 这里忘了 dc
            update(ans, dp[n][1][dc(i)]);
        }

        std::printf("%d\n", ans);
    }

    return 0;
}