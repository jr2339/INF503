//
//  Trie.c
//  PartA
//
//  Created by jr2339 on 4/1/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Trie.h"


//Returns new trie node (initialized to NULLS)
struct TrieNode *getNode(void){
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    
    if (pNode) {
        
        pNode -> isLeaf = false;
        
        for (int i=0; i<ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

void insert(struct TrieNode *root, const char *key, int size){
    int level;
    //int length = strlen(key);
    int index;
    
    struct TrieNode *pCrawl = root;
    
    for (level = 0; level < size; level++) {
        
        index = CHAR_TO_INDEX(key[level]);
       
       
        if (!pCrawl->children[index]) {
            pCrawl -> children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
        
    }
    //mark last node as leaf
    pCrawl->isLeaf = true;
    
}

bool search(struct TrieNode *root, const char* key){
    int level;
    int length = ALPHABET_SIZE;
    int index;
    
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index]) {
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    
    return (pCrawl !=NULL && pCrawl->isLeaf);
}

