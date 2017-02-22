import random

def get_sequence(length):
    DNA_Sequence = ""
    for i in range(length):
        DNA_Sequence += random.choice("AGCT")
    return DNA_Sequence

hash_table = {}

for i in range(100):
    sequence = get_sequence(16)
    hash_table[hash(sequence)] = sequence

print(hash_table)
