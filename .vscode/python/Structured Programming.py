n = int(input())
# nについて、3の倍数と、3を含む数を出力するようなプログラム。
# 3を含む数とは、「iを10で割った数が3)」と、思うが、例えば334とかはどう考える…？
for i in range(1, (n+1)):
	if (i % 3 == 0 or i % 10 == 3 or i//100 == 3):
		x = i
		print(" ",x, end="")
	else:
		pass
