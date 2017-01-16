import sys

# error checking
if len(sys.argv) != 2:
    print("Pass a keyword please!")
    exit(1)

if not sys.argv[1].isalpha():
    print("Only letters please!")
    exit(2)

# message and key
message, key = input(), list(sys.argv[1].upper())
encrypted_message, extended_key = [], []

# make a new extended key that is the key repeating
i = 0
while len(extended_key) <= len(message):
    if message[i].isalpha():
        extended_key.append(ord(key[i % len(key)]))
    else:
        extended_key.append(0)
    i += 1

# make a key
dict_key = dict(zip(message, extended_key))
print(extended_key)
