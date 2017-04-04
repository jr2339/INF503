//
//  Trie.h
//  PartA
//
//  Created by jr2339 on 4/1/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Trie_h
#define Trie_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define ALPHABET_SIZE 36



//Converts key current character into index
#define CHAR_TO_INDEX(letter) ((int)letter - (int)'A')


//trie node
struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    
    //isLeaf is true if the node represents
    //end of a word
    bool isLeaf;
};


struct TrieNode *getNode(void);
void insert(struct TrieNode *root, const char *key, int size);
bool search(struct TrieNode *root, const char* key);

#endif /* Trie_h */
