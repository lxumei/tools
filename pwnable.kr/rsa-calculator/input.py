from pwn import *
import binascii

p = process("./rsa_calculator")
gdb.attach(p)

def enc(aInt):
    return pow(aInt, 17) % 3233

def enctext(aText):
    res = b''
    for ch in aText:
        res += binascii.hexlify(p32(enc(ch)))
    return res.decode('ascii')

p.recvuntil(">")
p.sendline("1")
p.sendline("61")
p.sendline("53")
p.sendline("17")
p.sendline("2753")

def m_decrypt(aMsg):
    p.recvuntil(">")
    p.sendline("3")
    tmp = enctext(aMsg)
    p.sendline("%d"%len(tmp))
    p.sendline(tmp)

input()
m_decrypt(b"%p")

p.interactive()

