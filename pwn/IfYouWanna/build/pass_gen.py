pw = "mora+cookie+nan+t4shi+swa11ow="
num = 0
for a in pw:
  num += ord(a)
pw += hex(num)[2:]
print(pw)

en = []

for a in pw:
  if a==pw[0]:
    en = en + [ord(a)+2]
  else:
    en = en + [en[-1]^(ord(a)+2)]

print(list(map(hex,en[:-3])))
