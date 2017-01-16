# get height
height = int(input("height: "))
while height not in range(1, 24):
    height = int(input("Retry: "))

for i in range(height, 0, -1):
    spaces, hashes = " " * (i - 1), "#" * (height - (i - 1))
    print(spaces, end="")
    print(hashes, end=" ")
    print(hashes, end="")
    print(spaces)
