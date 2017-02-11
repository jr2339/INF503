//
//  main.c
//  Part1
//
//  Created by jr2339 on 2/10/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

//tring to random generate 100,000 nonrepeat number

//Generate 100,000 random nucleotide sequence fragments
char** Random_Sequence(int row,int column){

    //time_t t;
    //srand((unsigned)time(&t));
    int rand_number;
    char** sequence;
    sequence =(char**) malloc(row*column*sizeof(char*));
    for (int i=0; i<row; i++) {
        sequence[i] = (char*)malloc(column*sizeof(char));
        for (int j=0; j<column; j++) {
            
            rand_number = rand()%4;
            
            if (rand_number == 0) {
                *(sequence[i]+j) = 'A';
            }
            else if (rand_number == 1){
                *(sequence[i]+j) = 'C';
            }
            else if (rand_number == 2){
                *(sequence[i]+j) ='G';
            }
            else{
                *(sequence[i]+j) ='T';
            }

        }

    }

    return sequence;
    
}


int main(int argc, const char * argv[]) {
    int column = 16;
    int row = 100000 ;
    // insert code here...
    char **sequence;
    sequence = Random_Sequence(row,column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c", *(sequence[i]+j));
        }
        printf("\n");

    }
    return 0;
}
