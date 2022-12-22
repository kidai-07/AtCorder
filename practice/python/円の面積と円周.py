r = float(input()) ## 実数としかかいてない

d = "{:.5f}".format(float(r * r * 3.141592653589))
L = "{:.5f}".format(float(2 * r * 3.141592653589))

print(d,L)