//
//  main.c
//  Part2
//
//  Created by jr2339 on 2/12/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

int main(int argc, const char * argv[]) {
    /*
    if (argc < 2) {
        perror("We need more arguments");
        exit(1);
    }
    else if(argc > 2){
        perror("Too many arguments");
    }
    long n = atoi(argv[1]);
    long size = pow(4, n);
    char** sequence =(char**)malloc(size*sizeof(char*));
    
    sequence = generate_sequence(n);
    */
    char set[]={'A','C','G','T'};
    char arr[100]="";
    generate_sequence(set, arr, 0, 4, 10);
   
    return 0;
}
