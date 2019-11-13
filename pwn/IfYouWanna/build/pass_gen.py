pw = "swallow"
en = []

for a in pw:
  if a==pw[0]:
    en = en + [ord(a)+2]
  else:
    en = en + [en[-1]^(ord(a)+2)]

print(map(hex,en))
