import json
from Crypto.Util.number import inverse

with open('values.json', 'r') as file:
    data = json.load(file)

p = data['p']
q = data['q']
N = data['N']
e = data['e']
d = inverse(e, (p - 1) * (q - 1))
flag = 'flag{As_I_said,_D0_N0T_USE_ECB!}'
