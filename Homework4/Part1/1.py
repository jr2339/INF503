import random
import time

#Initialize The Matrix
class Diection():
    END = 0
    UP = 1
    LEFT = 2
    DIAGONAL = 3


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



def Needleman_Wunsch(Seq1,Seq2,GAP_Penalty,Match_Score,Mis_Match):
    m,n = len(Seq1),len(Seq2)

    # create score table with initial values of zero

    Score = Matrix_Zeros(Seq1,Seq2)


    #Generate DP table and traceback path pointer matrix
    for i in range(0,m+1):
        Score[i][0] = GAP_Penalty * i

    for j in range(0,n+1):
        Score[0][j] = GAP_Penalty * j

    for i in range(1,m+1):
        for j in range(1,n+1):
            match = Score[i-1][j-1] + match_score(Seq1[i-1],Seq2[j-1],GAP_Penalty,Match_Score,Mis_Match)
            delete = Score[i-1][j] + GAP_Penalty
            insert = Score[i][j-1] + GAP_Penalty
            Score[i][j] = max(match,delete,insert)

    #Traceback and compute the alignment
    Align1 = ''
    Align2 = ''
    i,j = m,n # start from the bottom right cell
    while i>0 and j>0: # end toching the top or the left edge
        score_current = Score[i][j]
        score_diagonal = Score[i-1][j-1]
        score_up = Score[i][j-1]
        score_left = Score[i-1][j]

        if score_current == score_diagonal + match_score(Seq1[i-1],Seq2[j-1],GAP_Penalty,Match_Score,Mis_Match):
            Align1 += Seq1[i-1]
            Align2 += Seq2[j-1]
            i -= 1
            j -= 1
        elif score_current == score_left + GAP_Penalty:
            Align1 += Seq1[i-1]
            Align2 += '_'
            i -= 1
        elif score_current == score_up + GAP_Penalty:
            Align1 += '_'
            Align2 += Seq2[j-1]
            j -= 1

    #Finish tracing up to the top left cell
    while i > 0:
        Align1 += Seq1[i-1]
        Align2 += '_'
        i -= 1
    while j > 0:
        Align1 += '_'
        Align2 += Seq2[j-1]
        j -= 1

    print_Align(Align1, Align2,GAP_Penalty,Match_Score,Mis_Match)

def get_sequence(length):
    DNA_Sequence = ""
    for i in range(length):
        DNA_Sequence += random.choice("AGCT")
    return DNA_Sequence


Sequence_A = get_sequence(1000)
Sequence_B = get_sequence(1000)
Sequence_C = get_sequence(10000)
Sequence_D = get_sequence(100000)
Sequence_E = get_sequence(1000000)

#Needleman_Wunsch('GATTA','GCTA',-1,5,-1)

start_time = time.time()
Needleman_Wunsch(Sequence_A,Sequence_D,-1,5,-1)

print("--- %s seconds ---" % (time.time() - start_time))
