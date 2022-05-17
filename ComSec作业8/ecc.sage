p = 11
A = 1
B = 6
E = EllipticCurve(GF(p),[0,0,0,A,B])
print("all points in E:")
print(E.points())



G = E([2,7])
#10.14
for i in range(2,14):
	output = i*G
	print(i,"G:",output)






