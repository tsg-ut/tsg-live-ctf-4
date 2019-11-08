import pickle
import json
import math
import random
from Crypto.Util.number import isPrime
from sympy.ntheory import factorint

def factor(n):
    i = 2
    while n % i != 0:
        i += 1
    return i

def get_prime():
    X = int(('0' * 63 + '1') * 37 + '0' * 89)

    factors_a = [2, 5, 11, 13, 23, 37, 53, 59]
    factors_b = [3, 7, 17, 19, 29, 31, 41, 47]

    prime_a = 1
    prime_b = 1

    while not isPrime(prime_a * X + prime_b):
        prime_a = 1
        while not (prime_a < 1e64 and prime_a >= 5e63):
            while prime_a < 5e63:
                prime_a *= random.choice(factors_a)
            while prime_a >= 1e64:
                factors = factorint(prime_a)
                prime_a //= random.choice(list(factors.keys()))
        print(prime_a)

        prime_b = 1
        counter = 0
        while not isPrime(prime_a * X + prime_b) and counter <= 100:
            prime_b = 1
            while not (prime_b < 1e89 and prime_b >= 5e88):
                while prime_b < 5e88:
                    prime_b *= random.choice(factors_b)
                while prime_b >= 1e89:
                    factors = factorint(prime_b)
                    prime_b //= random.choice(list(factors.keys()))
            counter += 1

    return prime_a * X + prime_b

p = get_prime()
print("Generated p...")
q = get_prime()
print("Generated q...")

with open('values.json', 'w') as file:
    json.dump({
        'N': p * q,
        'e': 2019112409,
        'p': p,
        'q': q,
    }, file)
