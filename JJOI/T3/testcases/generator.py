import random
datas = [
    [],
    [1, 1, 50],
    [10, 100, 150],
    [30, 1300, 2000],
    [100, 1300, 2000],
    [100, 15000, 20000]
]
SQ = "square{}.in"
i = 1;
while i <= 5:
    f = open(SQ.format(i),mode="w")
    f.write("{}\n".format(datas[i][0]))
    for _ in range(datas[i][0]):
        f.write("{}\n".format(random.randint(datas[i][1], datas[i][2])))
    i+=1