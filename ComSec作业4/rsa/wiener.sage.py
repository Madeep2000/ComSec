

# This file was *autogenerated* from the file wiener.sage
from sage.all_cmdline import *   # import sage library

_sage_const_0 = Integer(0); _sage_const_1 = Integer(1); _sage_const_2 = Integer(2); _sage_const_10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531469002933770824382865926730400902798743137187335810705309884635534159797732259520594337385186897629868362414475309001507719259272508669419676508606630823351242964205044695669333236417591 = Integer(10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531469002933770824382865926730400902798743137187335810705309884635534159797732259520594337385186897629868362414475309001507719259272508669419676508606630823351242964205044695669333236417591); _sage_const_10335071977839588495324343307012721241868030345867699233451500809021555989403028103743221782417440900848403102247012012875905268518785845678756696925714007988778268752026049276281025329038071087021446834856566687537729918372863729292015978809506607411711073716898691660211835403800810547133032654209857 = Integer(10335071977839588495324343307012721241868030345867699233451500809021555989403028103743221782417440900848403102247012012875905268518785845678756696925714007988778268752026049276281025329038071087021446834856566687537729918372863729292015978809506607411711073716898691660211835403800810547133032654209857); _sage_const_4 = Integer(4)#sage
def rational_to_contfrac(x,y):
    # Converts a rational x/y fraction into a list of partial quotients [a0, ..., an]
    a = x // y
    pquotients = [a]
    while a * y != x:
        x, y = y, x - a * y
        a = x // y
        pquotients.append(a)
    return pquotients

def convergents_from_contfrac(frac):
    # computes the list of convergents using the list of partial quotients
    convs = [];
    for i in range(len(frac)): convs.append(contfrac_to_rational(frac[_sage_const_0  : i]))
    return convs

def contfrac_to_rational (frac):
    # Converts a finite continued fraction [a0, ..., an] to an x/y rational.
    if len(frac) == _sage_const_0 : return (_sage_const_0 ,_sage_const_1 )
    num = frac[-_sage_const_1 ]
    denom = _sage_const_1 
    for _ in range(-_sage_const_2 , -len(frac) - _sage_const_1 , -_sage_const_1 ): num, denom = frac[_] * num + denom, num
    return (num, denom)

#e = 14058695417015334071588010346586749790539913287499707802938898719199384604316115908373997739604466972535533733290829894940306314501336291780396644520926473

#n = 33608051123287760315508423639768587307044110783252538766412788814888567164438282747809126528707329215122915093543085008547092423658991866313471837522758159
n = _sage_const_10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531469002933770824382865926730400902798743137187335810705309884635534159797732259520594337385186897629868362414475309001507719259272508669419676508606630823351242964205044695669333236417591 
e = _sage_const_10335071977839588495324343307012721241868030345867699233451500809021555989403028103743221782417440900848403102247012012875905268518785845678756696925714007988778268752026049276281025329038071087021446834856566687537729918372863729292015978809506607411711073716898691660211835403800810547133032654209857 

def egcd(a, b):
    if a == _sage_const_0 : return (b, _sage_const_0 , _sage_const_1 )
    g, x, y = egcd(b % a, a)
    return (g, y - (b // a) * x, x)

def mod_inv(a, m):
    g, x, _ = egcd(a, m)
    return (x + m) % m

def isqrt(n):
    x = n
    y = (x + _sage_const_1 ) // _sage_const_2 
    while y < x:
        x = y
        y = (x + n // x) // _sage_const_2 
    return x
  
def crack_rsa(e, n):
    frac = rational_to_contfrac(e, n)
    convergents = convergents_from_contfrac(frac)
    
    for (k, d) in convergents:
        if k != _sage_const_0  and (e * d - _sage_const_1 ) % k == _sage_const_0 :
            
            phi = (e * d - _sage_const_1 ) // k
            s = n - phi + _sage_const_1 
            # check if x*x - s*x + n = 0 has integer roots
            D = s * s - _sage_const_4  * n
            if D >= _sage_const_0 :
                sq = isqrt(D)
                if sq * sq == D and (s + sq) % _sage_const_2  == _sage_const_0 : return d

d = crack_rsa(e, n)

print(d)

