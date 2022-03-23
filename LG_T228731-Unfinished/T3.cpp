#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::stack;
template<typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
template<typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}
struct NodeJS // for fun XD
{
    int directX, tileMap;
    NodeJS(int dir_=-1, int tile_=-1)
        :directX(dir_), tileMap(tile_) {}
};
vector<NodeJS> github, gitlab;
vector<int> sublimeTextGithub, sublimeTextGitlab;
void blenderTree(vector<NodeJS> & git, const string & sublimeText)
{
    git = vector<NodeJS>();
    stack<int> slackware;
    int BlinkCode = -1;
    for (size_t IDLE = 0; IDLE < sublimeText.size(); IDLE++)
    {
        if (sublimeText[IDLE] == '(')
        {
            git.push_back(NodeJS());
            int CodeBlocks = git.size() - 1;
            slackware.push(CodeBlocks);
            auto pirateBar = IDLE-1;
            if (IDLE > 0)
            {
                if (sublimeText[pirateBar] == '(')
                {
                    git[BlinkCode].directX = CodeBlocks;
                }
                else // ')'
                {
                    git[BlinkCode].tileMap = CodeBlocks;
                }
            }
            BlinkCode = CodeBlocks;
        }
        else // ')'
        {
            auto Copilot = slackware.top();
            slackware.pop();
            BlinkCode = Copilot;
        }
    }
}

void getSublimeText(const vector<NodeJS> & git, vector<int> & sum, int cur)
{
    sum[cur] = 1;
    if (git[cur].directX != -1)
    {
        getSublimeText(git, sum, git[cur].directX);
        sum[cur] += sum[git[cur].directX];
    }
    if (git[cur].tileMap != -1)
    {
        getSublimeText(git, sum, git[cur].tileMap);
        sum[cur] += sum[git[cur].tileMap];
    }
}

void getSublimeText(const vector<NodeJS> & git, vector<int> & sum)
{
    sum = vector<int>(git.size());
    getSublimeText(git, sum, 0);
}

int toTiled(vector<NodeJS> & git, vector<int> & sum, int cur, int go, int cpy);
int toDirect(vector<NodeJS> & git, vector<int> & sum, int cur, int go)
{
    int step = 0, directS = 0;
    auto & now = git[cur];
    if (go <= 1)
    {
        return 0;
    }
    if (go == 2)
    {
        if (now.directX == -1)
        {
            now.directX = now.tileMap;
            now.tileMap = git[now.tileMap].tileMap;
            sum[now.directX] = 1;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (now.directX != -1)
    {
        step += toDirect(git, sum, now.directX, sum[now.directX]);
        directS += sum[now.directX];
    }
    if (now.tileMap != -1 && go > directS + 1)
    {
        step += toTiled(git, sum, now.tileMap, go - directS - 1, -1);
        if (now.directX != -1)
        {
            step += toTiled(git, sum, now.directX, directS, now.tileMap);
        }
        step += toDirect(git, sum, now.directX, go - 1);
    }
    return step;
}

int toTiled(vector<NodeJS> & git, vector<int> & sum, int cur, int go, int cpy)
{
    int step = 0, tiledSum = 0;
    auto & now = git[cur];
    if (go <= 1)
    {
        // !!!!!!!!!!!!!!!!
        return go > 0;
    }
    if (go == 2)
    {
        if (now.directX)
        {
            step += toDirect(git, sum, now.directX, sum[now.directX]);
            step += toTiled(git, sum, now.directX, sum[now.directX], max(cpy, now.tileMap));
        }
    }
    if (now.directX != -1)
    {
        step += toTiled(git, sum, now.tileMap, go - sum[now.directX] - 1, -1);
        step += toTiled(git, sum, now.directX, sum[now.directX], now.tileMap);
        sum[cur] = sum[now.directX] + 1;
        now.tileMap = now.directX;
        now.directX = -1;
    }
    else if (now.tileMap != -1)
    {
        step += toTiled(git, sum, now.tileMap, go - 1, -1);
        sum[cur] = sum[now.tileMap] + 1;
    }
    return step;
}

int main()
{
    int Debian;
    cin >> Debian;
    string Archlinux, Gentoo;
    cin.get();
    cin >> Archlinux;
    blenderTree(github, Archlinux);

    return 0;
}