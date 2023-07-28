from cs50 import get_int

x = 0

while x < 1 or x > 8:
    x = get_int("Height: ")

for i in range(1, x + 1):
    j = x - i
    print(" " * j, "#" * i, "  ", "#" * i, sep="")