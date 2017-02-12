//
//  main.c
//  Part1
//
//  Created by jr2339 on 2/10/17.
//  Copyright © 2017 jr2339. All rights reserved.
//



#include "sequence.h"
#include "hashTable.h"







int main(int argc, const char * argv[]) {
    
    HashTable H = InitializeTable(HashArraSize);
    long* sequence_number = sequence_to_number();
    
    insertToHashtable(sequence_number,H);
   
    return 0;
}
