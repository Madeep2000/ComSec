
import gmpy2 as gp
def egcd(a, b):
	if a == 0:
		return (b, 0, 1)
	else:
		g, y, x = egcd(b % a, a)
		return (g, x - (b // a) * y, y)

n = 1889570071
c1 = 1244183534
c2 = 732959706
e1 = 1021763679
e2 = 519424709
s = egcd(e1, e2)
s1 = s[1]
s2 = s[2]
if s1<0:
	s1 = - s1
	c1 = gp.invert(c1, n)
	
elif s2<0:
	s2 = - s2
	c2 = gp.invert(c2, n)
	
m = pow(c1,s1,n)*pow(c2,s2,n) % n
print(m)



import binascii
p =  20873
q =  90527
e =  1021763679
c =  1244183534
n = 1889570071
assert n == p*q
phi = (p-1)*(q-1)
d = gp.invert(e,phi)
m = pow(c,d,n)
print(m)
print(bytes.fromhex(hex(m)[2:]))