#!/usr/bin/env python3
import json
from secret import N, e, d, p, q, flag
from Crypto.Cipher import AES
from Crypto.PublicKey import RSA

assert(len(str(p)) == 2457)
assert(len(str(q)) == 2457)
assert(len(flag) == 32)

def pad(data):
    pad_size = AES.block_size - len(data) % AES.block_size
    return data + pad_size * bytes([pad_size])

rsa = RSA.construct((N, e, d, p, q))

pub = json.dumps({'N': N, 'e': e}).encode()
priv = json.dumps({'N': N, 'e': e, 'p': p, 'q': q, 'd': d}).encode()

aes = AES.new(flag, AES.MODE_ECB)
priv_enc = aes.encrypt(pad(priv))
flag_enc = rsa.encrypt(flag.encode(), None)[0]

open('pub.json', 'wb').write(pub)
open('priv.json.enc', 'wb').write(priv_enc)
open('flag.enc', 'wb').write(flag_enc)