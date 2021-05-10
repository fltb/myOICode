#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BigInt
{
    vector<int> Val;
public:
    BigInt(){}
    virtual ~BigInt(){}
    BigInt(int x);
    const BigInt operator+(const BigInt & x);
    const BigInt & operator=(int x);
    friend std::ostream & operator<<(std::ostream & os, const BigInt & x);
};

BigInt::BigInt(int x)
{
    string Tmp;
    Tmp = to_string(x);
    string::iterator it = Tmp.end();
    while(it != Tmp.begin())
    {
        --it;
        Val.push_back( (*it) - '0');
    }
}
const BigInt BigInt::operator+(const BigInt & x)
{
    BigInt a;
    int SizeA = Val.size(),
        SizeB = x.Val.size(),
        f = 0;
    if(SizeA < SizeB)
    {
        for(int i = 0; i < SizeA; ++i)
        {
            int Tmp = Val[i] + x.Val[i] + f;
            f = Tmp / 10;
            Tmp %= 10;
            a.Val.push_back(Tmp);
        }
        for(int i = SizeA; i < SizeB; ++i)
        {
            int Tmp = x.Val[i] + f;
            f = Tmp / 10;
            Tmp %= 10;
            a.Val.push_back(Tmp);
        }
        if(f != 0)
        {
            a.Val.push_back(f);
        }
    }
    else
    {
        for(int i = 0; i < SizeB; ++i)
        {
            int Tmp = Val[i] + x.Val[i] + f;
            f = Tmp / 10;
            Tmp %= 10;
            a.Val.push_back(Tmp);
        }
        for(int i = SizeB; i < SizeA; ++i)
        {
            int Tmp = Val[i] + f;
            f = Tmp / 10;
            Tmp %= 10;
            a.Val.push_back(Tmp);
        }
        if(f != 0)
        {
            a.Val.push_back(f);
        }
    }

    return a;
}
const BigInt & BigInt::operator=(int x)
{
    (*this) = BigInt(x);
    return *this;
}

std::ostream & operator<<(std::ostream & os, const BigInt & x)
{
    vector<int>::const_iterator it = x.Val.end();
    while(it != x.Val.begin())
    {
        os << *(--it);
    }
    return os;
}

BigInt Ans[1000 + 3];


int main()
{
    int n,m,All;
    BigInt ValN, ValM;
    cin>>m>>n;
    All = n - m + 1;
    Ans[0] = 0;
    Ans[1] = 1;
    for(int i = 1; i < All; ++i)
    {
        Ans[i + 1] = Ans[i] + Ans[i - 1];
    }
    cout << Ans[All];
    return 0;
}
