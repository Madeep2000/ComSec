# xor == add == sub


#output:a*(x**(times)) , a是多项式
def inner_mul(a,times):
    if times == 0:
        return a
    
    elif a > 127:
        a = a<<1
        a = a % 256
        a = a^27
        
            
    else:
        a = a<<1
        
        
    times = times - 1
    return inner_mul(a,times)


#input: a,b ∈ GF(2**8)
#output: a*b
def mul(a,b):
    result = 0
    bb = '{:08b}'.format(b)
    bb = bb[::-1]
    for i in range(8):
        if(bb[i] == '1'):
            result = result^inner_mul(a,i)
            
        else:
            pass
        
    return result


#input: 0 <= a <= 255
#output:a的二进制比特长度
def length(a):
    #return len(bin(a)[2:])
    leng = 0
    while(a):
        a = a>>1
        leng = leng + 1
    return leng


#input:被除数a，除数b
#output: q = a/b , r = a % b
def division(a,b):
    len1=length(a)
    len2=length(b)
    len3=len1-len2

    if a<b:                   #被除数小于除数
        if len3==0:           #两个数的长度相同，则直接商1，余数是二者异或的结果
            return (1,a^b)
        else:
            return (0,a)      #如果被除数的位数小于除数，则商0，余数为a
                
    topBit=1                  
    topBit<<=(len1-1)
    b<<=len3                  #把b的位数扩充到和a一致

    quotient=0
    remainder=0

    for i in range(len3):
        quotient<<=1        
        if (topBit&a):      
            quotient^=1     
            a^=b
        else:
            a^=0
        topBit>>=1          
        b>>=1

        
    quotient<<=1            
    if a<b:
        remainder=a
    else:
        quotient^=1
        remainder=a^b

    return quotient,remainder    


#input:m>n
#output:gcd(m,n)
def gcd(m,n):
    while(n!=0):
        m,n=n,m%n
    return m


#input:m>n ,gcd(m,n) == 1
#output:inverse of n 
def xgcd(m,n):
    r0,r1,s0,s1=1,0,0,1
    while(n):
        qq,rr=division(m,n)
        q,m,n=qq,n,rr
        r0,r1=r1,r0^mul(q,r1)
        s0,s1=s1,s0^mul(q,s1)
    return s0


#列变换
def substitution(inverse):

    inbit = '{:08b}'.format(inverse)
    inbit = inbit[::-1]

    temp = []
    for i in range(8):
        temp.append(int(inbit[i]))
    
    res = [0,0,0,0,0,0,0,0]
    #res = temp
    
    c = [1,1,0,0,0,1,1,0]
    result = 0
    for i in range(8):
        res[i] = temp[i]^temp[(i+4)%8]^temp[(i+5)%8]^temp[(i+6)%8]^temp[(i+7)%8]^c[i]
        result += res[i]*(2**i)
        

    
    return hex(result)
    


def creat_sbox():
    box = []
    sbox = 0x0
    
    for i in range(256):
        sbox=substitution(xgcd(283,i))           #283代表不可约多项式：x**8+x**4+x**3+x+1
        box.append(sbox)
        
    for j in range(256):
        print(box[j],end=' ')
        if (j+1)%16==0:
            print('\n')



#--------------main-----------------:
creat_sbox()




