//
//  sequence.c
//  Part1
//
//  Created by jr2339 on 2/11/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "sequence.h"
//Generate 100,000 random nucleotide sequence fragments
char** Random_Sequence(int row,int col){
    
    time_t t;
    srand((unsigned)time(&t));
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

long* sequence_to_number(){
    int row = HashArraSize ;
    int coefficent[row][column] ;
    long* total = malloc(row * sizeof(long));
    char **sequence;
    sequence = Random_Sequence(row,column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            //printf("%c", *(sequence[i]+j));
            if ( *(sequence[i]+j) == 'A') {
                coefficent[i][j] = 0;
            }
            else if( *(sequence[i]+j) == 'C'){
                coefficent[i][j] = 1;
            }
            else if (*(sequence[i]+j) == 'G'){
                coefficent[i][j] = 2;
            }
            else{
                coefficent[i][j] = 3;
            }
            
        }
        
        *(total+i)= coefficent[i][0]*pow(4,15)+coefficent[i][1]*pow(4,14)+coefficent[i][2]*pow(4,13)+coefficent[i][3]*pow(4,11)+coefficent[i][4]*pow(4,10)+coefficent[i][5]*pow(4,9)+coefficent[i][6]*pow(4,8)+coefficent[i][7]*pow(4,7)+coefficent[i][8]*pow(4,6)+coefficent[i][9]*pow(4,5)+coefficent[i][10]*pow(4,4)+coefficent[i][11]*pow(4,3)+coefficent[i][12]*pow(4,2)+coefficent[i][13]*pow(4,1)+coefficent[i][14]*pow(4,1)+coefficent[i][15]*pow(4,0);
         
       
    }
    return total;
}













