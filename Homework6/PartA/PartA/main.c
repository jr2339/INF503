//
//  main.c
//  PartA
//
//  Created by jr2339 on 3/29/17.
//  Copyright © 2017 jr2339. All rights reserved.
//




//If not present, inserts key into tire
//If the key is prefix of trie node, just marks leaf node



#include "Genome.h"
#include "Trie.h"





int main(int argc, const char * argv[]) {
    // insert code here...
    if(argc < 4){
        perror("We need 4 arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if (argc > 4){
        perror("Too many arguments, we only need 4 arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    int number = atoi(argv[1]);
    int size = atoi(argv[2]);
    
    /*open the input DENV2.txt file*/
    const char* input = argv[3];
    
    if (input == NULL) {
        fprintf(stderr, "Error: main: Failed to open input file '%s'\n", argv[3]);
        exit(1);
    }

    struct TrieNode *root = getNode();

    char** Sequence;
    Sequence = get_sequence(number, size,input);
    
   
    for (int i=0; i<number; i++) {
        //printf("%d we will insert------------------->%s\n",i+1,Sequence[i]);
        insert(root, Sequence[i],size+1);
        printf("%s ---> %s\n", Sequence[i], Sequence[search(root, Sequence[i])]);
        }
   
    return 0;
}
