//
//  main.cpp
//  SuffixTree
//
//  Created by jr2339 on 4/7/17.
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
        fprintf(stderr, "Error: main: Failed to open input file '%s'\n", argv[2]);
        exit(1);
    }
    
    
    
    char* DNA = (char*)malloc(size*sizeof(char));
    DNA = get_sequence(size,input);
    cout <<"DNA Sequence is:"<< DNA <<endl;
    SuffixTree tree(DNA);
    string stringList= DNA;
    
        
        vector<int> li = tree.getIndexes(stringList);
        if (li.size() != 0) {
            cout << stringList << "  ";
            cout << li[1]<< " ";
            cout << endl;
        }
    
    
    
    return 0;
}

