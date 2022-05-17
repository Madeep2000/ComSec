from Crypto.Cipher import AES
from binascii import *

def padding_pkcs5(value):
    BS = AES.block_size
    return str.encode(value + (BS - len(value) % BS) * chr(BS - len(value) % BS), encoding='utf-8')

key = b'Tover_LOVE_c10udlnk!!!!!'
aes = AES.new(key, AES.MODE_ECB)
text = 'And c10udlnk LOVE Tover too. So when can see Tover wear dress? [LookForward!]'
print(len(hexlify(text.encode())))
text = padding_pkcs5(text)
cipher = aes.encrypt(text)
print(hexlify(key))
print(hexlify(text))
print(hexlify(cipher))
