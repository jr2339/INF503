//
//  hashTable.c
//  Part1
//
//  Created by jr2339 on 2/11/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "hashTable.h"

HashTable InitializeTable(int Tablesize){
    HashTable H;
    if (Tablesize < 1) {
        fprintf(stderr,"table size is too small!");
        exit(0);
    }
    H = (HashTable)malloc(sizeof(struct HashTb));
    if (H == NULL) {
        fprintf(stderr,"out of space");
        exit(0);
    }

    H->TheList = (List*)malloc(sizeof(List)*HashArraSize);
    for (int i=0; i<HashArraSize; i++) {
        H->TheList[i]=(List)malloc(sizeof(struct ListNode));
        H->TheList[i]->Next = NULL;
    }
    
    return H;
}

int HashIndex(long key){
    return key%HashArraSize;
}


Position Find_Position(long key,HashTable H){
    int index = HashIndex(key);
    List L = H->TheList[index]->Next;
    while (L!=NULL&&L->element!=key) {
        L = L->Next;
    }
    return L;
}

void Insert(long key, HashTable H){
    if (Find_Position(key, H)== NULL) {
        int index = HashIndex(key);
        List L = (List)malloc(sizeof(struct ListNode));
        L->element = key;
        Position P = H->TheList[index];
        L->Next = P->Next;
        P->Next = L;
    }

}


void insertToHashtable(long* sequenceNumber,HashTable H){
    for (int i= 0; i<HashArraSize;i++) {
        printf("===================%ld\n",sequenceNumber[i]);
        Insert(sequenceNumber[i],H);
    }
   
}

/*
void display(int count,HashTable H){
    for (int i=0; i<HashArraSize; i++) {
        //printf("in %d, we have %lu\n",);
    }
}

 */
