a, b, c = map(int, input().split())

## aから bまでの整数の中に、cの約数がいくつあるかを求める

## 変数初期化
count = 0
i = 0

for i in range(a,b+1):
    if c % i == 0:
        count+=1
    i+=1

print(count)