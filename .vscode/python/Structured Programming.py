n = int(input())

for i in range (1,n+1):
    if i % 3 == 0:
        print(" ",i, end = "")
    else:
        x = i
        while x > 0:
            if x % 10 == 3:
                print(" ",i, end = "")
                break ##2重ループなので、ここで一回終わる必要がある
            x//=10