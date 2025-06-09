import random as rd

for n in range(10, 1001, 10):
    if n < 100:
        f = open(F"./cadena-00{n}.txt", 'w')
    elif n < 1000:
        f = open(F"./cadena-0{n}.txt", 'w')
    else:
        f = open(F"./cadena-{n}.txt", 'w')

    f.write(str(n) + "\n")
    I = []
    for i in range(0, n):
        I.append((i, i+3))

    rd.shuffle(I)

    for s, t in I:
        f.write(str(s) + " " + str(t) + "\n")

    f.close()