//
//  hashTable.h
//  Part1
//
//  Created by jr2339 on 2/11/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef hashTable_h
#define hashTable_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include "sequence.h"
#define HashArraSize 100000

typedef struct ListNode *Position;
typedef struct HashTb *HashTable;

struct ListNode{
    long element;
    Position Next;
};

typedef Position List;


struct HashTb{
    List *TheList;
};
HashTable InitializeTable(int Tablesize);
int HashIndex(long key);
Position Find_Position(long key,HashTable H);
void Insert(long key, HashTable H);
void insertToHashtable(long* sequenceNumber,HashTable H);
void display(int count,HashTable H);

#endif /* hashTable_h */
