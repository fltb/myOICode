int pow(int x, int p) {
    int ans = 1, base = x;
    while (p > 0)
    {
        if (p & 1)
        {
            ans *= base;
        }
        base *= base;
        p >>= 1;
    }
    return ans;
};