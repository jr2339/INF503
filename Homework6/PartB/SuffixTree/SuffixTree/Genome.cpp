//
//  Genome.cpp
//  SuffixTree
//
//  Created by jr2339 on 4/6/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Genome.hpp"

char* get_sequence(int size,const char* filename){
    
    time_t t;
    srand((unsigned)time(&t));
    int rand_number;
    
    
    FILE *fp = fopen(filename, "r");
    
    if (!fp) {
        fprintf(stderr, "Error: Could not open file\n");
        exit(1);
    }
    
    
    fseek(fp,0,SEEK_END);
    long fsize = ftell(fp);
    printf("The size is %lu\n", fsize);
    fseek(fp, 0, SEEK_SET);
    char* original = (char*)malloc(sizeof(char)*(fsize));
    
    char c;
    int count =0;
    for (c = getc(fp); c!=EOF; c=getc(fp)) {
        if (!isspace(c) && c !='\n') {
            original[count] = c;
            count = count + 1;
        }
        
    }
    
    /*
    char** sequence = (char**)malloc(number*sizeof(char*));
    for (int i=0; i<number; i++) {
        sequence[i] = (char*)malloc(size*sizeof(char));
        rand_number = rand() % (fsize-size*5);
        for (int j=0; j<size; j++) {
            *(sequence[i]+j)=original[rand_number+j];
            
        }
        printf("the random is %d, this is line %d ------------------>%s\n",rand_number,i+1,sequence[i]);
    }
    */
    char* sequence = (char*)malloc(size*sizeof(char));
    for (int i=0; i<size; i++) {
        //*(sequence[i]+j)=original[rand_number+j];
        rand_number = rand() % (fsize-size);
        sequence[i] = original[rand_number+i];
        
    }
    return sequence;
}
