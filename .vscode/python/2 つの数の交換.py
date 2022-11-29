i = 0
while i < 3000: # inputの数とずれているとエラーになる
	x, y = map(int, input().split())
	if (x==0) and (y==0):# インデントがおかしいとエラーになる,関数は基本小文字
		break
	numbers = [x,y]
	sorted_numbers = sorted(numbers)
	X = sorted_numbers[0]
	Y = sorted_numbers[1]
	print(X, Y)
	i += 1