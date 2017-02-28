import random
import numpy
#assume p =0.005 is the probability of success


#What is the average number of successes in 10,000 trials?

#Provide estimate of mean, 95% confidence interval and the code to obtain these results

def define_success():
    success = []
    for i in range(1000):
       random_number = random.randint(1,200)
       if random_number == 10:
           success.append(True)
       else:
           success.append(False)
    return success


def count():
    counter =[]

    for i in range(1000):
        coun =0
        result = define_success()
        for i in range(len(result)):
            if result[i] == True:
                coun = coun +1
        counter.append(coun)
    counter.sort()
    return counter

data = count()

data = data[50:950]
print(data)
average =numpy.mean(data)

print(average)
