//
//  Genome.cpp
//  SuffixTree
//
//  Created by jr2339 on 4/7/17.
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
    //printf("The size is %lu\n", fsize);
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
    
    
    char* sequence = (char*)malloc(size*sizeof(char));
    for (int i=0; i<size; i++) {
        
        rand_number = rand() % (fsize-size);
        sequence[i] = original[rand_number+i];
        
    }
    return sequence;
}

