from Crypto.Cipher import AES
from binascii import b2a_hex, a2b_hex
 
 
message = "需要加密的信息"
key = 'aes_keysaes_keysaes_keys'
mode = AES.MODE_OFB
cryptor = AES.new(key.encode('utf-8'), mode, b'0000000000000000')
length = 16
count = len(message)
if count % length != 0:
    add = length - (count % length)
else:
    add = 0
message = message + ('\0' * add)
ciphertext = cryptor.encrypt(message.encode('utf-8'))
result = b2a_hex(ciphertext)
print(result.decode('utf-8'))
 
cryptor = AES.new(key.encode('utf-8'), mode, b'0000000000000000')
plain_text = cryptor.decrypt(a2b_hex(result))
print(plain_text.decode('utf-8').rstrip('\0'))


'''
# encoding:utf-8
import base64
from Crypto.Cipher import AES
from Crypto import Random
 
def encrypt(data, password):
    bs = AES.block_size
    pad = lambda s: s + (bs - len(s) % bs) * chr(bs - len(s) % bs)
    iv = Random.new().read(bs)
    cipher = AES.new(password, AES.MODE_CBC, iv)
    data = cipher.encrypt(pad(data))
    data = iv + data
    return (data)
 
def decrypt(data, password):
    bs = AES.block_size
    if len(data) <= bs:
        return (data)
    unpad = lambda s : s[0:-ord(s[-1])]
    iv = data[:bs]
    cipher = AES.new(password, AES.MODE_CBC, iv)
    data  = unpad(cipher.decrypt(data[bs:]))
    return (data)
 
if __name__ == '__main__':
    data = 'd437814d9185a290af20514d9341b710'
    password = '78f40f2c57eee727a4be179049cecf89' #16,24,32位长的密码
    encrypt_data = encrypt(data, password)
    encrypt_data = base64.b64encode(encrypt_data)
    print ('encrypt_data:', encrypt_data)
 
 
    encrypt_data = base64.b64decode(encrypt_data)
    decrypt_data = decrypt(encrypt_data, password)
    print ('decrypt_data:', decrypt_data)
'''