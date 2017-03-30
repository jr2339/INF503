import random
import time

#Initialize The Matrix
class Diection():
    END = 0
    UP = 1
    LEFT = 2
    DIAGONAL = 3
#################################################################################################################
def delete_all_space():
    file = open("DENV2.txt", "r")
    DNA_Sequence = ""
    for line in file.readlines():
        content = line.split()

    for i in range(len(content)):
        DNA_Sequence += content[i]

    return DNA_Sequence


def get_sequence():
    DNA_Dictionary = dict()
    Original_Sequence = delete_all_space()
    ######################################Generate seed List######################################
    Word =[]
    for i in range(len(Original_Sequence)-11+1):
        Word.append(Original_Sequence[i:i+11])
    ######################################Generate Index######################################
    Index = []
    for i in range(len(Word)):
        Index.append(i)

    for i in range(len(Word)):
        if Word[i] in DNA_Dictionary:
            DNA_Dictionary[Word[i]].append(Index[i])
        else:
            DNA_Dictionary[Word[i]] = [Index[i]]

    return DNA_Dictionary



def get_file():
    output = open('index.txt','w')
    DNA_Dictionary = get_sequence()
    output.write(str(DNA_Dictionary))
    output.close()






def get_index_seeds():
    index_file = open("index.txt", "r")
    Based_dictionary = eval(index_file.read())
    index_file.close()
    return Based_dictionary


def get_test_seeds():
    test_file = open("test.txt", "r")
    data = test_file.readlines()

    head_size = 9
    Sequence_size = 50
    Test_Query = []
    i=0
    while i < (len(data[0])-11+1):
        Test_Query.append(data[0][i+head_size:i+head_size+Sequence_size])

        i += head_size+Sequence_size+1
    return Test_Query











def compare(read):
    Query ="NULL"
    DENV2_Index_Seeds = get_index_seeds()
    for i in range(len(read)-11+1):
        for key in DENV2_Index_Seeds:
            if read[i:i+11] == key:
                if key ==0 and i !=0:
                    Query ="NULL"
                else:
                    Query = read
                break

    return Query







#####################################################################################################################



def Matrix_Zeros(Seq1,Seq2):
    Matrix = []
    for i in xrange(len(Seq1)+1):
        Matrix.append([])
        for j in xrange(len(Seq2)+1):
            Matrix[-1].append(0)
    return Matrix


def match_score(alpha,beta,GAP_Penalty,Match_Score,Mis_Match):
    if alpha == beta:
        return Match_Score
    elif alpha == '_' or beta == '_':
        return GAP_Penalty
    else:
        return Mis_Match

def print_Align(Align1, Align2,GAP_Penalty,Match_Score,Mis_Match):
    Align1 = Align1[::-1] #reverse Sequence 1
    Align2 = Align2[::-1] #reverse Sequence 2

    i,j =0,0
    #calculate identity, score and aligned sequences

    symbol =''
    found = 0
    score = 0
    identity = 0

    for i in range(0,len(Align1)):
        #if two char are, then output the letter
        if Align1[i] == Align2[i]:
            symbol = symbol + '|'
            identity = identity + 1
            score += match_score(Align1[i],Align2[i],GAP_Penalty,Match_Score,Mis_Match)

        #if two char are not identical and nonne of them is a GAP
        elif Align1[i] != Align2[i] and Align1[i] != '_' and Align2[i] != '_':
            score += match_score(Align1[i], Align2[i], GAP_Penalty, Match_Score, Mis_Match)
            symbol = symbol + 'X'
            found = 0

        #if one the these char is a GAP, output a space
        elif Align1[i] == '_' or Align2[i] == '_':
            symbol = symbol + ' '
            score += GAP_Penalty

    identity = float(identity) / (100*len(Align1))

    #print('Identify=',"%3.3f" % identity,'percent')
    #print('Score =', score)
    print Align1
    print symbol
    print Align2



def Smith_Waterman(Seq1,Seq2,GAP_Penalty,Match_Score,Mis_Match):
    m,n = len(Seq1),len(Seq2)

    # create score table with initial values of zero
    # create trace table with initial values of zero
    Score = Matrix_Zeros(Seq1,Seq2)
    Trace = Matrix_Zeros(Seq1,Seq2)

    #initial maximum score in Score Table
    max_score = 0

    #Calculate Score Table and Trace
    for i in range(1,len(Seq1)+1):
        for j in range(1,len(Seq2)+1):

            score_diagonal = Score[i-1][j-1] + match_score(Seq1[i-1],Seq2[j-1],GAP_Penalty,Match_Score,Mis_Match)
            score_up = Score[i][j-1] + GAP_Penalty
            score_left = Score[i-1][j] + GAP_Penalty
            Score[i][j] = max(0,score_left,score_up,score_diagonal)

            if Score[i][j] == 0:
                Trace[i][j] = Diection.END

            if Score[i][j] == score_left:
                Trace[i][j] = Diection.UP

            if Score[i][j] == score_up:
                Trace[i][j] = Diection.LEFT

            if Score[i][j] == score_diagonal:
                Trace[i][j] = Diection.DIAGONAL

            if Score[i][j] >= max_score:
                max_i = i
                max_j = j
                max_score = Score[i][j]

    # initial sequences
    Align1, Align2 = '',''

    i,j = max_i, max_j

    #traceback, follow Trace
    while Trace[i][j] != 0:
        if Trace[i][j] == 3:
            Align1 += Seq1[i-1]
            Align2 += Seq2[j-1]
            i -= 1
            j -= 1

        elif Trace[i][j] == 2:
            Align1 += '_'
            Align2 += Seq2[j-1]
            j -= 1

        elif Trace[i][j] == 1:
            Align1 += Seq1[i-1]
            Align2 += '_'
            i -= 1
    print_Align(Align1, Align2,GAP_Penalty,Match_Score,Mis_Match)


Sequence = delete_all_space()

#####################################################################################################################

def test():
    Test_Query = get_test_seeds()
    Valid_Query = {}


    for i in range(len(Test_Query)):
        if compare(Test_Query[i]) != "NULL":
            Valid_Query[i] = Test_Query[i]

    for key in Valid_Query:
        print("==============================read_%d"+str(key+1)+"==============================")
        Smith_Waterman(Test_Query[key],Sequence,-1,5,-1)







test()






