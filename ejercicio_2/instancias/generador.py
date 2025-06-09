import random as rd

for n in range(10, 1001, 10):
    m = 50
    if n < 10:
        f = open(F"./m-fijo-000{n}.txt", 'w')
    elif n < 100:
        f = open(F"./m-fijo-00{n}.txt", 'w')
    elif n < 1000:
        f = open(F"./m-fijo-0{n}.txt", 'w')
    else:
        f = open(F"./m-fijo-{n}.txt", 'w')

    f.write(str(m) + " " + str(n) + "\n")
    for i in range(0, m):
        for j in range(0, n-1):
            f.write(str(rd.randint(0, 1)) + " ")
        f.write(str(rd.randint(0, 1)) + "\n")

    f.close()

for m in range(10, 1001, 10):
    n = 50
    if m < 10:
        f = open(F"./n-fijo-000{m}.txt", 'w')
    elif m < 100:
        f = open(F"./n-fijo-00{m}.txt", 'w')
    elif m < 1000:
        f = open(F"./n-fijo-0{m}.txt", 'w')
    else:
        f = open(F"./n-fijo-{m}.txt", 'w')

    f.write(str(m) + " " + str(n) + "\n")
    for i in range(0, m):
        for j in range(0, n-1):
            f.write(str(rd.randint(0, 1)) + " ")
        f.write(str(rd.randint(0, 1)) + "\n")

    f.close()