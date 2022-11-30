a, b = map(int, input().split())

d = a // b
r = a % b
f = "{:.5f}".format(float(a) / float(b),)

print(d,r,f)
