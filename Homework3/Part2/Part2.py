import random
import numpy

def define_bacterial():
    Bacterial = []
    for i in range(100000):
       random_number = random.randint(1,100000)
       if random_number < 1001:
           Bacterial.append('M') #False means mutant bacterial
       else:
           Bacterial.append('N') #False means normal bacterial
    return Bacterial

def random_select():
    Selected_Bacterial =[]
    Bacterial = define_bacterial()
    for i in range(1000):
        random_number = random.randint(0,99999)
        Selected_Bacterial.append(Bacterial[random_number])
    return Selected_Bacterial

def count():
    counter =[]
    for i in range(1000):
        coun = 0
        result = random_select()
        for i in range(len(result)):
            if result[i] == 'M':
                coun = coun + 1
        counter.append(coun)
    counter.sort()
    return counter

data = count()
average =numpy.mean(data)
print(average)
data = data[50:950]
print(data)
