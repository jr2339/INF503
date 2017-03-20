import random
#define the EACH CEll for the Matrix
#Each Cell has value and diection to next Cell
class Matrix_Component:
    def __init__(self,value,direction):
        self.value = value
        self.direct = direction

    def __str__(self):
        print(str[self.value,self.direct])

import numpy as np

#define Needleman-Wunsch algorithm function
def nw(Seq1,Seq2,GAP_Penalty,Match_Score,Mis_Match):

    # initialize the array
    # matrix = np.zeros([len(seq2)+1, len(seq1)+1])

    Matrix = [[Matrix_Component(0,-1) for i in range(len(Seq1)+1)] for j in range(len(Seq2)+1)]
    #print('rows:' + str(len(Matrix)))
    #print('cols:' + str(len(Matrix[0])))

    #initialize first row and column with multiples of gap penalty
    for i in range(0,len(Seq1)+1):
        Matrix[0][i] = Matrix_Component(i*GAP_Penalty,-1)
    for j in range(0,len(Seq2)+1):
        Matrix[j][0] = Matrix_Component(j*GAP_Penalty,-1)

    #generate values in remaining Matrix_Component
    for row in range(1,len(Seq2)+1):
        for col in range(1,len(Seq1)+1):
            possible_value = All_Possible_Value([row,col],GAP_Penalty,Match_Score,Mis_Match,Matrix,Seq1,Seq2)

            Matrix[row][col] = Choose_Max(possible_value)

    return Matrix

#define All Possible Vale, We have 3 direction to get 3 different Value in Each Cell
def  All_Possible_Value(Currect_Position, GAP_Penalty,Match_Score,Mis_Match,Matrix,Seq1,Seq2):
    #print([Seq1[Currect_Position[1]-1],Seq2[Currect_Position[0]-1]])
    if Seq1[Currect_Position[1]-1] == Seq2[Currect_Position[0]-1]:
        Diag = Match_Score + Matrix[Currect_Position[0]-1][Currect_Position[1]-1].value
    else:
        Diag = Mis_Match + Matrix[Currect_Position[0]-1][Currect_Position[1]-1].value

    possible_value = [GAP_Penalty+Matrix[Currect_Position[0]][Currect_Position[1]-1].value,
                      GAP_Penalty + Matrix[Currect_Position[0]-1][Currect_Position[1]].value,
                      Diag]
    #print("===============================================")
    return possible_value

#define Choose_Max, choose the biggest value from possible value
#Max is a Compoent in the Matrix
#0: Left; 1: Up; 2: Diag
def Choose_Max(value):
    Max = Matrix_Component(value[0],0)
    for i in range(0,len(value)):
        if value[i] > Max.value:
            Max.value = value[i]
            Max.direct = i
    return Max

def print_Matrix(Matrix):
    Obj = np.zeros([len(Matrix),len(Matrix[0])])

    for row in range(len(Matrix)):
        for col in range(len(Matrix[0])):
            Obj[row,col] = Matrix[row][col].value
    print(Obj)

def Build_Align(Matrix, Seq1, Seq2):
    rows = len(Matrix)
    cols = len(Matrix[0])

    Aligns = ['',
              '',
              '']

    r = rows - 1
    c = cols - 1

    while(r!=0 and c!=0 and Matrix[r][c].direct != -1):
        #print('direct: ' + str(Matrix[r][c].direct))
        #print('[r:c]:' + str([r,c]))

        if Matrix[r][c].direct == 0:
            Aligns[0] += Seq1[c-1]
            Aligns[1] += ' '
            Aligns[2] += '-'
            c = c-1
        elif Matrix[r][c].direct == 1:
            Aligns[0] += '-'
            Aligns[1] += ' '
            Aligns[2] += Seq2[r-1]
            r = r-1
        elif Matrix[r][c].direct == 2:
            Aligns[0] += Seq1[c-1]
            Aligns[2] += Seq2[r-1]
            c = c-1
            r = r-1
            if Aligns[0][-1] == Aligns[2][-1]:
                Aligns[1] += '|'
            else:
                Aligns[1] += 'x'

    Aligns = [Aligns[0][::-1],Aligns[1][::-1], Aligns[2][::-1]]
    return Aligns

def Print_Align(Matrix, Seq1, Seq2):
    Aligns = Build_Align(Matrix, Seq1, Seq2)
    for i in range(len(Aligns)):
        print(Aligns[i])

def get_sequence(length):
    DNA_Sequence = ""
    for i in range(length):
        DNA_Sequence += random.choice("AGCT")
    return DNA_Sequence

#This is the Part A in our homework
Matrix = nw('ACTCG', 'ACAGTAG', -3, 5, -1)
Print_Align(Matrix, 'ACTCG', 'ACAGTAG')
print("\n")
#Now, Generate 1K, 10K, 100K, and 1M (million) random genomic sequences (100nt) to use as targets for alignment
# and 1 sequence to use as a query.
#================================================1k,1k================================================
Sequence_A = get_sequence(1000)
Sequence_B = get_sequence(1000)
Sequence_C = get_sequence(10000)
Sequence_D = get_sequence(100000)
Sequence_E = get_sequence(1000000)
Matrix = nw(Sequence_A,Sequence_B, -3, 5, -1)
Print_Align(Matrix, Sequence_A, Sequence_B)
print("\n")

#================================================1k,10k================================================
Matrix = nw(Sequence_A,Sequence_C, -3, 5, -1)
Print_Align(Matrix, Sequence_A, Sequence_C)
print("\n")

#================================================1k,10k================================================
Matrix = nw(Sequence_D,Sequence_C, -3, 5, -1)
Print_Align(Matrix, Sequence_D, Sequence_C)
print("\n")

#================================================10,100k================================================
Matrix = nw(Sequence_D,Sequence_E, -3, 5, -1)
Print_Align(Matrix, Sequence_D, Sequence_E)
print("\n")