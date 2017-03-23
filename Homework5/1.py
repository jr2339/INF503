import random

def get_sequence(length):
    DNA_Sequence = ""
    for i in range(length):
        DNA_Sequence += random.choice("ACGT")
        return DNA_Sequence


def get_success(length):
    success = []
    for i in range(length):
        random_number = random.randint(1,100)
        if random_number == 10:
            success.append(True)
        else:
            success.append(False)
    return success



def Sequence(length):
    Original_Sequence = get_sequence(length)
    squence = ""
    success = get_success(length)
    for i in range(length):
        if success[i] == True:
            squence += Original_Sequence[i]
        else:
            if Original_Sequence[i] == 'A':
                squence += random.choice("CGT")
            elif Original_Sequence[i] == 'C':
                squence += random.choice("AGT")
            elif Original_Sequence[i] == 'G':
                squence += random.choice("ACT")
            else:
                squence += random.choice("ACG")
    return squence


def count(length,size):
    counter = []
    Original_Sequence = get_sequence(length)
    sequence = Sequence(length)
    for i in range(100):
        coun = 0
        for j in range(length - size):
            if Original_Sequence[j:j+size-1] == sequence[j:j+size-1]:
                coun = coun + 1
        counter.append(coun)
    return counter

count(36,30)
