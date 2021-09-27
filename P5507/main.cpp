#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
const int Buttons = 12, BestStep = 17 + 1;

int Relates [Buttons+1][5], SWorst;

void SetRelates(int X, int A, int B, int C, int D)
{
    Relates[X][1] = A;
    Relates[X][2] = B;
    Relates[X][3] = C;
    Relates[X][4] = D;
}

//Buttons

/* Test of state function
    int a = 12,b = 2;
    int ABit = 4, BBit = 1;
    int State = 0;
    SetStateOfButton(State,a,ABit);
    SetStateOfButton(State,b,BBit);
    cout<<GetStateOfButton(State,a)<<" "<<GetStateOfButton(State,b);
*/
int GetStateOfButton(int States, int X)
{
    int Bit = 3;
    Bit &= States>>(X<<1);
    return ++Bit;
}

bool SetStateOfButton(int & States, int X, int S)
{
    if(S > 4 || S <= 0 || X > 12)
    {
        return false;
    }
    int BitC = 3;
    BitC <<= (X<<1);
    BitC = ~BitC;
    States &= BitC;
    S -= 1;
    S <<= (X<<1);
    States |= S;
    return true;
}

bool SetSteps(int & States, int Step)
{
    if(31 < Step)
    {
        return false;
    }
    int BitC = 31;
    BitC <<= ((Buttons+1)<<1);
    BitC = ~BitC;
    States &= BitC;
    Step <<= ((Buttons+1)<<1);
    States |= Step;
    return true;
}

int GetSteps (int States)
{
    int Step = 31;
    Step = (States>>((Buttons+1)<<1));
    return Step;
}

//Walks
bool WalkSingle(int & States, int X)
{
    int S = GetStateOfButton(States, X);
    if (S > 4 || S <= 0)
    {
        //assert(1);
        return false;
    }
    if (S == 4)
    {
        SetStateOfButton(States,X, 1);
    }
    else
    {
        SetStateOfButton(States,X, S + 1);
    }
    return true;
}

bool Walk (int & State, int X)
{
    int S = GetStateOfButton(State,X);
    int Step = GetSteps(State);
    WalkSingle(State, X);
    WalkSingle(State, Relates[X][S]);
    SetSteps(State, Step + 1);
}
int Steps[BestStep + 1];

void dfs (int SNow)
{

}

int main()
{
    freopen("out.txt","w",stdout);
    int SDefault = 0;

    for(int i = 1; i <= Buttons; ++i)
    {
        int S,A,B,C,D;
        cin >> S >> A >> B >> C >> D;
        SetStateOfButton(SDefault,i,S);
        SWorst += S;
        SetRelates(i,A,B,C,D);
    }

    return 0;
}
