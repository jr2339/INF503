import random #to generate random int

#assume p =0.005 is the probability of success


#What is the average number of failures until the first success?

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
                break
            else:
                coun = coun +1
        counter.append(coun)
    counter.sort()
    return counter

data = count()

data = data[5:995]
print(data)

