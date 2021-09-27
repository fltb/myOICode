#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;

class BigInt
{
public:
    std::vector<int> arr;
    enum {POWER = 3, BASE = 1000};
    // init begin::
    BigInt(){}
    ~BigInt(){}
    BigInt & operator=(const BigInt & x);
    BigInt(const BigInt & x){ *this = x;}
    BigInt(const int x) { *this = BigInt(std::to_string(x) ); };
    BigInt(const std::string x);
    // init end::

    // calculation begin::
    const BigInt operator+(const BigInt & x);
    const BigInt operator-(const BigInt & x);
    const BigInt operator*(const BigInt & x);
    const BigInt operator/(const BigInt & x);
    const BigInt operator%(const BigInt & x);
    // calculation end::

    // output
    friend std::ostream & operator<<(std::ostream & os, const BigInt & x);

};

BigInt::BigInt(const std::string x)
{
    arr.clear();
    int len, cur, aaa = 0, cnt = 1;
    len = x.length();
    cur = len;
    //cout << "x = " << x << endl;
    while (cur)
    {
        --cur;
        int pow = (len - cur) % BigInt::POWER;
        //cout << "pow = " << pow <<endl;
        aaa += cnt * (x[cur] - '0');
        cnt *= 10;
        //cout << "aaa = " << aaa << endl;
        if (0 == pow)
        {
            arr.push_back(aaa);
            aaa = 0;
            cnt = 1;
        }
        
    }
    if (aaa)
    {
        arr.push_back(aaa);
    }
}

BigInt & BigInt::operator=(const BigInt & x)
{
    if(!x.arr.empty()) arr = std::vector<int>(x.arr);
    return (*this);
}

const BigInt BigInt::operator+(const BigInt & x) 
{
    BigInt now = BigInt();
    if (x.arr.empty())
    {
        return *this;
    }
    if (arr.empty())
    {
        return x;
    }
    auto it1 = arr.begin();
    auto it2 = x.arr.begin();
    int  aaa = 0;
    while (it1 != arr.end() && it2 != x.arr.end() )
    {
        aaa += *it1 + *it2;
        now.arr.push_back(aaa % BigInt::BASE);
        aaa /= BigInt::BASE;
        ++it1;
        ++it2;
    }
    if (aaa)
    {
        if (it1 != arr.end())
        {
            now.arr.push_back(*it1 + aaa%BigInt::BASE);
            aaa /= BigInt::BASE;
            ++it1;
        }
        else if (it2 != x.arr.end())
        {
            now.arr.push_back(*it2 + aaa%BigInt::BASE);
            aaa /= BigInt::BASE;
            ++it2;
        }
        else 
        {
            now.arr.push_back(aaa);
        }
    }
    while (it1 != arr.end())
    {
        now.arr.push_back(*it1);
        ++it1;
    }
    while (it2 != x.arr.end())
    {
        now.arr.push_back(*it2);
        ++it2;
    }
    return now;
}

std::ostream & operator<<(std::ostream & os, const BigInt & x)
{
    if (x.arr.empty())
    {
        return os;
    }
    auto it = x.arr.end();
    --it;
    cout << *it;
    while (it != x.arr.begin())
    {
        --it;
        os << std::setfill('0') << std::setw(BigInt::POWER) << *it;
    } 
    return os;
}

int main()
{
    BigInt a("1234"), b("10001");
    std::string str;
    cin >> str;
    a = BigInt(str);
    cin.get();
    cin >> str;
    b = BigInt(str);
    cin.get();
    cout << a+b << endl;
}