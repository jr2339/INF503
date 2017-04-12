//
//  main.cpp
//  SuffisTrie
//
//  Created by jr2339 on 4/7/17.
//  Copyright © 2017 jr2339. All rights reserved.
//


#include "SuffixTrie.hpp"
#include "Genome.hpp"

int main(int argc, char *argv[])
{
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

    char* DNA = (char*)malloc((size+1)*sizeof(char));
    DNA = get_sequence(size,input);
    
    cout <<"DNA Sequence is:"<< DNA <<endl;
    SuffixTrie* trie = new SuffixTrie();
    
    trie->build_suffix_trie(DNA);
    
    SuffixNode* root = trie->get_trie_root();
    SuffixNode* longest = trie->get_deepest_leaf();
    
    cout << "print trie stucture: \n";
    output(root);
    //cout << "print suffix link: \n";
    //output_suffix(longest);
    
    
    
    /*
    string s = argv[1];
    string q = argv[2];
    
    SuffixTrie* trie = new SuffixTrie();
    trie->build_suffix_trie(s+SENTINEL);
    
    SuffixNode* root = trie->get_trie_root();
    SuffixNode* longest = trie->get_deepest_leaf();
    
    cout << "print trie stucture\n";
    output(root);
    cout << "print suffix link\n";
    output_suffix(longest);
    
    // test basic applications
    test_substring(trie, s, q);
    test_suffix(trie, s, q);
    test_occurrence(trie, s, q);
    test_longest_repeat(trie, s);
    test_lexico_first_suffix(trie, s);
     */
}
