#!/usr/bin/env python

sp = " " * 4
print(f" n{sp} f1{sp} f2{sp}f2/f1")
print("-" * 25)

for n in range(2,21):
  f1 = int((n /2) ** 2)
  f2 = n*(n-1)
  r = f2 / f1
  print(f"{n:2}{sp}{f1:3}{sp}{f2:3}{sp} {r:.2f}")
