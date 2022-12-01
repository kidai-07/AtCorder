n = int(input())
list = [map(int, input().split())]

sorted_list = [list.sort()]
sorted_list_r = [list.sort(reverse=True)]

mn = int(sorted_list[0])
mx = int(sorted_list_r[0])
sm = (mn + mx)

print(mn,mx,sm)

---データ型の指定エラーが出る