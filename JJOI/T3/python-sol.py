from math import sqrt
t = int(input())
while t > 0:
    n=int(input())
    ans = 0
    for fst in range(0, int(sqrt(n))+1):
        for scd in range(fst,int(sqrt(n-fst*fst))+1):
            for thd in range(scd, int(sqrt(n-fst*fst-scd*scd))+1):
                fth = int(sqrt(n-fst*fst-scd*scd-thd*thd))
                if fth < thd and fth * fth == n-fst*fst-scd*scd-thd*thd:
                    ans += 1
    print(ans)
    t-=1