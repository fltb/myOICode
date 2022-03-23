#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
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
template<typename T, int N>
class Stack
{
    T arr[N];
    int i;
public:
    Stack():i(0) {}
    void push(const T & item)
    {
        arr[i++] = item;
    }
    const T & top()
    {
        return arr[i-1];
    }
    void pop()
    {
        i--;
    }
    int size()
    {
        return i;
    }
    bool empty()
    {
        return i <= 0;
    }
};
