n = int(input())
a = list(map(int, input().split()))  # mapで受け取った場合、list()をかける必要がある

reversed_list = list(reversed(a))

for i, item in enumerate(reversed_list):  # 判定用と出力用に、変数を2個使っている
    if i == len(reversed_list) - 1:
        print(item)
    else:
        print(item,end = ' ')

        
