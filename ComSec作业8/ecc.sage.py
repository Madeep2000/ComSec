

# This file was *autogenerated* from the file ecc.sage
from sage.all_cmdline import *   # import sage library

_sage_const_11 = Integer(11); _sage_const_1 = Integer(1); _sage_const_6 = Integer(6); _sage_const_0 = Integer(0); _sage_const_2 = Integer(2); _sage_const_7 = Integer(7); _sage_const_14 = Integer(14)
p = _sage_const_11 
A = _sage_const_1 
B = _sage_const_6 
E = EllipticCurve(GF(p),[_sage_const_0 ,_sage_const_0 ,_sage_const_0 ,A,B])
print("all points in E:")
print(E.points())



G = E([_sage_const_2 ,_sage_const_7 ])
#10.14
for i in range(_sage_const_2 ,_sage_const_14 ):
	output = i*G
	print(i,"G:",output)







