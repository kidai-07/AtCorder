while True:
	H, W = map(int, input().split())
	if (H == 0 and W == 0):
		break
	for i in range(0,H):
		if (i == 0 or i == (H-1)):
			for j in range(0, W):
				print("#", end = "")
			print()
		else:
			for j in range (0,W):
				if (j == 0 or j == (W-1)):
					print("#", end = "")
				else:
					print(".", end = "")
			print()
	print()
