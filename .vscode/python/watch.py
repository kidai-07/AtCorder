S = int(input()) # 整数を受け取る
# 1h = 60min = 3600sec
# くり上がりの概念を実装する必要がある

h = S // 3600 
m = (S % 3600)//60
s = (S % 3600) % 60 

print(h,end=':')
print(m,end=':')
print(s)