N = int(input())
A = list(map(int,input().split())) ## mapで受け取った場合、list()をかける必要がある

x = min(A)
y = max(A)
z = sum(A)

print(x,y,z)