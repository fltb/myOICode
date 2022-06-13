#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iomanip>

using std::cin;
using std::cout;
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
const int MAXN  = 1000 + 2;
struct Man
{
    BigInt l;int r;
    Man(int l_=0, int r_=0) : l(l_), r(r_) {}
    bool operator<(const Man & x)
    {
        return l * r < x.l * x.r;
    }
};
Man mans[MAXN];
int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        mans[i] = Man(l, r);
    }
    std::sort(mans+1, mans+n+1);
    BigInt aaa(mans[0].l);
    BigInt ans(0);
    for (int i = 1; i <= n; i++)
    {
        const auto& man = mans[i];
        ans = max(ans, (aaa/man.r));
        aaa = aaa * man.l;
    }
    cout << ans << '\n';
    return 0;
}