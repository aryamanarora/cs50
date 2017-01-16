# get height
height = int(input("height: "))
while height not in range(1, 24):
    height = int(input("Retry: "))

# print pyramid
for i in range(height, 1, -1):
    # print spaces
    print(" " * (i - 1), end="")
    # prints hashes
    print("#" * (height - (i - 2)))
