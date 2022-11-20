from math import sqrt
t = int(input())
rec=[114514]*30000
for i in range(0, int(sqrt(30000))):
    rec[i*i]=i
while t > 0:
    n=int(input())
    ans = 0
    fst = 0
    l1 = int(sqrt(n))+1
    while fst < l1:
        scd = fst
        l2=int(sqrt(n-fst*fst))+1
        while scd < l2:
            thd = scd
            l3=int(sqrt(n-fst*fst-scd*scd))+1
            while thd < l3:
                fth = rec[sqrt(n-fst*fst-scd*scd-thd*thd)]
                if fth < thd and fth * fth == n-fst*fst-scd*scd-thd*thd:
                    ans += 1
                thd+=1
            scd+=1
        fst+=1
    print(ans)
    t-=1