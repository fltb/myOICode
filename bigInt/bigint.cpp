#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

class BigInt
{
   private:
    std::vector<int> arr;
    bool negative;

   public:
    static const int POWER = 4;
    static const int BASE = 10000;
    // init begin::
    BigInt() : negative(false) {}
    ~BigInt() {}
    const BigInt& operator=(const BigInt& x);
    BigInt(const BigInt& x) { *this = x; }
    BigInt(const int x) { *this = BigInt(std::to_string(x)); };
    BigInt(const std::string x);
    // init end::

    // calculation begin::
    const BigInt operator+(const BigInt& x) const;
    const BigInt operator-(const BigInt& x) const;
    const BigInt operator*(const BigInt& x) const;
    const BigInt operator/(const BigInt& x) const;
    const BigInt operator/(const int x) const;
    const BigInt operator%(const BigInt& x) const;
    // calculation end::

    // comparation begin::
    bool operator<(const BigInt& x) const;
    bool operator==(const BigInt& x) const;
    // comparation end::

    // output
    friend std::ostream& operator<<(std::ostream& os, const BigInt& x);
};

BigInt::BigInt(const std::string x)
{
    negative = false;
    arr.clear();
    int len, cur, aaa = 0, cnt = 1, begin = 0;
    if (x[0] == '-')
    {
        negative = true;
        begin = 1;
    }
    len = x.length();
    cur = len;
    while (cur > begin)
    {
        --cur;
        int pow = (len - cur) % BigInt::POWER;
        aaa += cnt * (x[cur] - '0');
        cnt *= 10;
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

const BigInt& BigInt::operator=(const BigInt& x)
{
    negative = x.negative;
    if (!x.arr.empty())
        arr = std::vector<int>(x.arr);
    return (*this);
}

const BigInt BigInt::operator+(const BigInt& x) const
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
    int aaa = 0;
    while (it1 != arr.end() && it2 != x.arr.end())
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
            now.arr.push_back(*it1 + aaa % BigInt::BASE);
            aaa /= BigInt::BASE;
            ++it1;
        }
        else if (it2 != x.arr.end())
        {
            now.arr.push_back(*it2 + aaa % BigInt::BASE);
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
    while (now.arr.back() == 0)
    {
        now.arr.pop_back();
    }
    return now;
}

const BigInt BigInt::operator-(const BigInt& x) const
{
    BigInt now = BigInt();
    if (x.arr.empty())
    {
        return *this;
    }
    if (arr.empty())
    {
        now = x;
        now.negative = true;
        return now;
    }

    if ((*this) < x)
    {
        now = x - (*this);
        now.negative = true;
        return now;
    }

    auto it1 = arr.begin();
    auto it2 = x.arr.begin();
    int aaa = 0;
    while (it2 != x.arr.end())
    {
        aaa += *it1 - *it2;
        if (aaa < 0)
        {
            now.arr.push_back(aaa + BigInt::BASE);
            aaa -= BigInt::BASE;
            aaa /= BigInt::BASE;
        }
        else
        {
            now.arr.push_back(aaa);
            aaa /= BigInt::BASE;
        }
        ++it1;
        ++it2;
    }

    while (it1 != arr.end())
    {
        aaa += *it1;
        if (aaa < 0)
        {
            now.arr.push_back(aaa + BigInt::BASE);
            aaa -= BigInt::BASE;
            aaa /= BigInt::BASE;
        }
        else
        {
            now.arr.push_back(aaa);
            aaa /= BigInt::BASE;
        }
        ++it1;
    }
    while (now.arr.back() == 0)
    {
        now.arr.pop_back();
    }
    return now;
}

const BigInt BigInt::operator*(const BigInt& x) const
{
    if (arr.empty() || x.arr.empty())
    {
        return BigInt(0);
    }
    BigInt now = BigInt();
    now.arr = std::vector<int>(arr.size() + x.arr.size());
    if (negative ^ x.negative)  // xor
    {
        now.negative = true;
    }

    auto it1 = arr.begin();
    auto it2 = x.arr.begin();
    int aaa = 0, cnt = 0, cur = 0;
    while (it2 != x.arr.end())
    {
        while (it1 != arr.end())
        {
            now.arr[cur + cnt] += aaa + ((*it1) * (*it2));
            aaa = now.arr[cur + cnt] / BigInt::BASE;
            now.arr[cur + cnt] %= BigInt::BASE;
            ++cnt;
            ++it1;
        }
        now.arr[cur + cnt] = aaa;
        aaa = 0;
        cnt = 0;
        it1 = arr.begin();
        ++it2;
        ++cur;
    }
    while (now.arr.back() == 0)
    {
        now.arr.pop_back();
    }
    return now;
}

const BigInt BigInt::operator/(int x) const
{
    if (arr.empty() || x == 0)
    {
        return BigInt(0);
    }
    BigInt now = BigInt();
    if (x < 0)
    {
        now.negative = !negative;
        x = 0 - x;
    }
    now.arr = std::vector<int>(arr.size(), 0);
    auto it = arr.end();
    auto it2 = now.arr.end();

    int yu = 0;
    do {
        --it;
        --it2;
        *it2 = (*it + yu * BASE) / x;
        yu = (*it + yu * BASE) % x;
    } while (it != arr.begin());

    while (!now.arr.empty() && now.arr.back() == 0)
    {
        now.arr.pop_back();
    }

    return now;
}

bool BigInt::operator==(const BigInt& x) const
{
    if (arr.size() != x.arr.size())
    {
        return false;
    }
    if (negative ^ x.negative)  // xor
    {
        return false;
    }
    auto it1 = arr.begin();
    auto it2 = x.arr.begin();
    while (it1 != arr.end())
    {
        if (*it1 != *it2)
        {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

bool BigInt::operator<(const BigInt& x) const
{
    if (arr.size() < x.arr.size())
    {
        return true;
    }
    else if (!(arr.size() == x.arr.size()))
    {
        return false;
    }
    if (!arr.size() || !x.arr.size())
    {
        return arr.size() < x.arr.size();
    }
    if (negative && (!x.negative))
    {
        return true;
    }
    else if ((!negative) && x.negative)
    {
        return false;
    }
    auto it1 = arr.end();
    auto it2 = x.arr.end();
    --it1;
    --it2;
    if (*it1 < *it2)
    {
        return true;
    }
    else if (*it1 > *it2)
    {
        return false;
    }
    while (it1 != arr.begin())
    {
        --it1;
        --it2;
        if (*it1 < *it2)
        {
            return true;
        }
        else if (*it1 > *it2)
        {
            return false;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const BigInt& x)
{
    if (x.arr.empty())
    {
        return os;
    }
    if (x.negative)
    {
        os << "-";
    }
    auto it = x.arr.end();
    --it;
    os << *it;
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
    int aa, bb;
    while (cin >> aa >> bb)
    {
        a = BigInt(aa);
        int b = bb;
        /*b = BigInt(bb);
        if (!(a + b == aa + bb))
        {
            cout << "BAD+" << endl;
            cout << "Right " << aa + bb << " Wrong " << a + b << endl;
        }
        if (!(a - b == BigInt(aa - bb)))
        {
            cout << "BAD-" << endl;
            cout << "Right " << aa - bb << " Wrong " << a - b << endl;
        }
        if (!(a * b == BigInt(aa * bb)))
        {
            cout << "BAD*" << endl;
            cout << "Right " << aa * bb << " Wrong " << a * b << endl;
        }*/
        if (!(a / b == BigInt(aa / bb)))
        {
            cout << "BAD/" << endl;
            cout << "Right " << aa / bb << " Wrong " << a / b << endl;
        }
    }
    return 0;
}