import random as rd

# for n in range(2, 101):
#     if n < 10:
#         f = open(F"./ciclo-00{n}.txt", 'w')
#     elif n < 100:
#         f = open(F"./ciclo-0{n}.txt", 'w')
#     else:
#         f = open(F"./ciclo-{n}.txt", 'w')

#     f.write(str(n) + " " + str(n) + "\n")

#     for i in range(0, n-1):
#         f.write(str(i) + " " + str(i+1) + " " + str(rd.randint(0, 2*n)) + "\n")
#     f.write(str(n-1) + " 0 " + str(rd.randint(0, 2*n)) + "\n")

#     f.close()

M = []
n = 100
for x in range(0, n):
    M.append(n - 1 - x)
    m = sum(M)
    
    if m < 100:
        f = open(F"./n-fijo-00{m}.txt", 'w')
    elif m < 1000:
        f = open(F"./n-fijo-0{m}.txt", 'w')
    else:
        f = open(F"./n-fijo-{m}.txt", 'w')
    
    f.write(str(n) + " " + str(m) + "\n")

    for i in range(0, x+1):
        for j in range(i+1, n):
            f.write(str(i) + " " + str(j) + " " + str(rd.randint(0, 2*n)) + "\n")

    f.close()