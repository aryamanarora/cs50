import sys
from string import ascii_lowercase, ascii_uppercase

# error checking, not enough/too many args, non integer
# rotation value
if len(sys.argv) != 2:
    print("Usage: python caesar.py rotation")
    exit(1)

try:
    rot = int(sys.argv[1])
except:
    print("Rotation must be an integer.")
    exit(2)

# get input and make variable for encoding
message = list(input())

# make key dictionary
# basically, the keys are the letters a-z + A-Z which
# are then joined with the letters ?-z + a-? + ?-Z + Z-?
key = dict(zip(ascii_lowercase + ascii_uppercase, ascii_lowercase[rot:] +
               ascii_lowercase[:rot] + ascii_uppercase[rot:] +
               ascii_uppercase[:rot]))


def encoder(char):
    # apparently it's bad to assign a lambda to a variable,
    # so this encodes a message but only if the characters
    # are in the key
    return key[char] if char in key else char


# make the encoded message
encoded_message = "".join(encoder(char) for char in message)
print(encoded_message)
