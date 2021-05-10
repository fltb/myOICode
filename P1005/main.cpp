#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

class BigInt
{
    public:
        vector<int>s;
        bool is_minus=0;

        friend ostream& operator << (ostream &out,const BigInt& x);
        friend istream& operator >> (istream &in,BigInt& x);

        BigInt (long long num=0){*this=num;}
        BigInt (const string& num){*this=num;}
        BigInt (const char num[]){*this = string(num);}
        BigInt operator = (long long num)
        {
            s.clear();
            while(num)
            {
                s.push_back(num%10);
                num/=10;
            }
            return *this;
        }
        BigInt operator = (const string& str)
        {
            s.clear();
            for(int i=str.size()-1;i>=0;i--)
            {
                s.push_back(str[i]-'0');
            }
            return *this;
        }
        BigInt operator + (const BigInt& b)const
        {
            BigInt c;
            int msize=max(b.s.size(),s.size())+1;
            for(int i=0;i<msize;i++)
                c.s.push_back(0);
            for(int i=0;i<b.s.size();i++)
                c.s[i]+=b.s[i];
            for(int i=0;i<s.size();i++)
            {
                c.s[i]+=s[i];
                if(c.s[i]>=10)
                {
                    c.s[i+1]++;
                    c.s[i]-=10;
                }
            }
            for(int i=0;i<msize-1;i++)
            {
                if(c.s[i]>=10)
                {
                    c.s[i+1]++;
                    c.s[i]-=10;
                }
            }
            c.clean_zero();
            return c;
        }

        bool operator < (const BigInt& b)const
        {
            if(s.size()>b.s.size())
                return false;
            if(s.size()<b.s.size())
                return true;
            for(int i=s.size()-1;i>=0;i--)
            {
                if(s[i]>b.s[i])
                    return false;
                if(s[i]<b.s[i])
                    return true;
            }
            return false;
        }
        bool operator == (const BigInt& b)const
        {
            return s==b.s;
        }
        BigInt operator - (const BigInt& b)const
        {
            BigInt x,y;
            if(*this<b)
                x=b,y=*this,x.is_minus=1;
            else
                x=*this,y=b;
            while(y.s.size()<x.s.size())
                y.s.push_back(0);
            for(int i=0;i<x.s.size();i++)
            {
                x.s[i]-=y.s[i];
                if(x.s[i]<0)
                {
                     x.s[i]+=10;
                     x.s[i+1]--;
                }
            }
            x.clean_zero();
            return x;
        }
        BigInt operator * (const BigInt& b)const
        {
            BigInt c;
            unsigned long long need=s.size()+b.s.size();
            while(c.s.size()<need)
                c.s.push_back(0);
            for(unsigned long long i=0;i<s.size();i++)
                for(unsigned long long j=0;j<b.s.size();j++)
                    c.s[i+j]+=s[i]*b.s[j];
            for(int i=0;i<need-1;i++)
            {
                c.s[i+1]+=c.s[i]/10;
                c.s[i]%=10;
            }
            c.clean_zero();
            return c;
        }

        inline void clean_zero()
        {
            auto it=s.end()-1;
            while((*it)==0)
            {
                if(s.empty())
                    break;
                s.erase(it--);
            }
        }

        void clear()
        {
            s.clear();
            is_minus=0;
        }

    friend ostream& operator << (ostream &out,const BigInt& x)
    {

        if(x.is_minus && !x.s.empty())
            out<<'-';
        for(int i=x.s.size()-1;i>=0;i--)
            out<<x.s[i];
        if(x.s.size()==0)
            out<<0;
        return out;
    }

    friend istream& operator >> (istream &in,BigInt& x)
    {
        string s;
        if(!(in>>s))return in;
        x=s;
        return in;
    }

};

BigInt N_2[83] =
{
    "1",
"2",
"4",
"8",
"16",
"32",
"64",
"128",
"256",
"512",
"1024",
"2048",
"4096",
"8192",
"16384",
"32768",
"65536",
"131072",
"262144",
"524288",
"1048576",
"2097152",
"4194304",
"8388608",
"16777216",
"33554432",
"67108864",
"134217728",
"268435456",
"536870912",
"1073741824",
"2147483648",
"4294967296",
"8589934592",
"17179869184",
"34359738368",
"68719476736",
"137438953472",
"274877906944",
"549755813888",
"1099511627776",
"2199023255552",
"4398046511104",
"8796093022208",
"17592186044416",
"35184372088832",
"70368744177664",
"140737488355328",
"281474976710656",
"562949953421312",
"1125899906842624",
"2251799813685248",
"4503599627370496",
"9007199254740992",
"18014398509481984",
"36028797018963968",
"72057594037927936",
"144115188075855872",
"288230376151711744",
"576460752303423488",
"1152921504606846976",
"2305843009213693952",
"4611686018427387904",
"9223372036854775808",
"18446744073709551616",
"36893488147419103232",
"73786976294838206464",
"147573952589676412928",
"295147905179352825856",
"590295810358705651712",
"1180591620717411303424",
"2361183241434822606848",
"4722366482869645213696",
"9444732965739290427392",
"18889465931478580854784",
"37778931862957161709568",
"75557863725914323419136",
"151115727451828646838272",
"302231454903657293676544",
"604462909807314587353088",
"1208925819614629174706176",
"2417851639229258349412352",
"4835703278458516698824704"
};

const int MAXN = 80 + 3;

BigInt F[MAXN][MAXN][MAXN] ,A[MAXN][MAXN];


int N,M;
int main()
{
    cin>>N>>M;
    for(int i = 1; i <= N; ++i)
    {
        for(int j = 1; j <= M; ++j)
        {
            int Tmp;
            scanf("%d",&Tmp);
            A[i][j] = Tmp;
        }
    }

    for(int T = 1; T <= N; ++T)
    {
        //for(int len = M; len > 0; --len)
        for(int i = 1; i <= M; ++i)
        {

            //for(int i = 1; i + len - 1 <= N; ++i)
            for(int j = M; j >= i; --j)
            {
                //int j = i + len - 1;
                int len = j - i + 1;
                F[T][i][j] = max(F[T][i-1][j] + A[T][i-1]*N_2[M-len], F[T][i][j+1] + A[T][j+1]*N_2[M-len]);
            }
        }
    }
    BigInt Ans;
    for(int T = 1; T <= N; ++T)
    {
        BigInt Tmp;
        for(int i = 1; i <= M; ++i)
        {
            Tmp = max( Tmp, F[T][i][i] + A[T][i]*N_2[M]);
        }
        Ans = Ans + Tmp;
    }
    cout<<Ans;
}

