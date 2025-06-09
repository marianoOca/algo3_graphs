# -- no geodesico, n = m
for n in range(0, 1000, 10):
    if n < 10:
        f = open(F"./no-geo-00{n}.txt", 'w')
    elif n >= 10 and n < 100:
        f = open(F"./no-geo-0{n}.txt", 'w')
    else:
        f = open(F"./no-geo-{n}.txt", 'w')
    
    f.write(str(n) + " " + str(n) + "\n")
    for i in range(0, n-1):
        f.write(str(i) + " " + str(i+1) + "\n")
    f.write(str(n-1) + " 0\n")

    f.close()

# -- geodesico, n = m
for n in range(1, 1001, 10):
    if n < 10:
        f = open(F"./geo-00{n}.txt", 'w')
    elif n >= 10 and n < 100:
        f = open(F"./geo-0{n}.txt", 'w')
    else:
        f = open(F"./geo-{n}.txt", 'w')
    
    f.write(str(n) + " " + str(n) + "\n")
    for i in range(0, n-1):
        f.write(str(i) + " " + str(i+1) + "\n")
    f.write(str(n-1) + " 0\n")

    f.close()

# -- n = 100 fijo
M = []
for x in range(0, 100):
    M.append(100 - 1 - x)
    m = sum(M)
    
    if m < 100:
        f = open(F"./n-fijo-00{m}.txt", 'w')
    elif m >= 100 and m < 1000:
        f = open(F"./n-fijo-0{m}.txt", 'w')
    else:
        f = open(F"./n-fijo-{m}.txt", 'w')
    
    f.write("100 " + str(m) + "\n")

    for i in range(0, x+1):
        for j in range(i+1, 100):
            f.write(str(i) + " " + str(j) + "\n")

    f.close()