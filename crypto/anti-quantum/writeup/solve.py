#!/usr/bin/env python2
from sage.all import *
from Crypto.Cipher import AES
from Crypto.PublicKey import RSA
import json

with open('../problem/pub.json', 'r') as file:
    pub = json.load(file)

N = pub['N']
e = pub['e']

X = int(('0' * 63 + '1') * 37 + '0' * 89)

A = N // (X ** 2)
B = N % (X ** 2) // X
C = N % X

assert(A * X ** 2 + B * X + C == N)

print('A = {}'.format(factor(A)))
print('C = {}'.format(factor(C)))

bc = var('bc')
solve = solve(bc ** 2 - B * bc + A * C, bc, solution_dict = True)[0]

bc_value = solve[bc].pyobject()
print('bc = {}'.format(bc_value))

a_prime = A + B - bc_value
c_prime = bc_value + C
b_plus_d = gcd(a_prime, c_prime)
print('b+d = {}'.format(b_plus_d))

a = a_prime / b_plus_d
c = c_prime / b_plus_d
b = A / a
d = C / c
print('a = {}'.format(a))
print('b = {}'.format(b))
print('c = {}'.format(c))
print('d = {}'.format(d))

p = a * X + c
q = b * X + d
print('p = {}'.format(p))
print('q = {}'.format(q))

assert(p * q == N)

d = inverse_mod(e, int((p - 1) * (q - 1)))
rsa = RSA.construct((N, long(e), int(d), int(p), int(q)))

with open('../problem/flag.enc', 'rb') as file:
    flag_enc = file.read()

flag = rsa.decrypt(flag_enc)
print('')
print(flag)