//
//  main.cpp
//  SuffixTree
//
//  Created by jr2339 on 4/5/17.
//  Copyright © 2017 jr2339. All rights reserved.
//


#include "SuffixTree.h"
#include "Genome.hpp"

int main(int argc, const char * argv[]){
    
    if(argc < 3){
        perror("We need 3 arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if (argc > 3){
        perror("Too many arguments, we only need 3 arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    
    //int number = atoi(argv[1]);
    int size = atoi(argv[1]);
    
    /*open the input DENV2.txt file*/
    const char* input = argv[2];
    
    if (input == NULL) {
        fprintf(stderr, "Error: main: Failed to open input file '%s'\n", argv[3]);
        exit(1);
    }
    
    /*
    char** Sequence;
    Sequence = get_sequence(number, size,input);
    char* DNA = (char*)malloc(number*size*sizeof(char));
    for (int i=0; i<number; i++) {
        
        for (int j=0; j<size; j++) {
            DNA[i*size+j] = *(Sequence[i]+j);
        }
    }
    printf("DNA Sequence is %s\n",DNA);

    SuffixTree tree(DNA);
    for (int i=0; i<number; i++) {
        vector<int> li = tree.getIndexes(Sequence[i]);
        if (li.size() !=0) {
            cout << Sequence[i] << ": ";
            for (int j=0; j<li.size(); ++j) {
                cout <<li[j] << " ";
            }
            cout << endl;
        }
        else{
            cout << Sequence[i] << ": can't find it" <<endl;
        }
    }*/
    
    char* DNA = (char*)malloc(size*sizeof(char));
    DNA = get_sequence(size,input);
    cout <<"DNA Sequence is:"<< DNA <<endl;
    return 0;
}


