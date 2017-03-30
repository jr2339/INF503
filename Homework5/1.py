import random
import numpy
def Simulation(length,size):


    #calculate the match
    counter = []


    for i in range(100000):
        # Generate Original Sequence
        Original_Sequence = ""
        for i in range(length):
            Original_Sequence += random.choice("ACGT")

        # calculate the 1% error
        """
        success = []
        for i in range(length):
            random_number = random.randint(1, 100)
            if random_number == 10:
                success.append(False)
            else:
                success.append(True)
        """

        #calculate the 5% error
        success = []
        for i in range(length):
            random_number = random.randint(1, 100)
            if random_number <=5:
                success.append(False)
            else:
                success.append(True)


        # calculate the error Sequence
        Finial_Squence = ""
        for i in range(length):
            if success[i] == True:
                Finial_Squence += Original_Sequence[i]
            elif success[i] == False:
                if Original_Sequence[i] == 'A':
                    Finial_Squence += random.choice("CGT")
                elif Original_Sequence[i] == 'C':
                    Finial_Squence += random.choice("AGT")
                elif Original_Sequence[i] == 'G':
                    Finial_Squence += random.choice("ACT")
                else:
                    Finial_Squence += random.choice("ACG")

        coun = 0
        for j in range(length - size+1):
            if Original_Sequence[j:j+size-1] == Finial_Squence[j:j+size-1]:
                coun = coun + 1

        counter.append(coun)
    average = numpy.mean(counter)
    return average

print(Simulation(36,30))