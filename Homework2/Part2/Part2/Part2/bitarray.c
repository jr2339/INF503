//
//  bitarray.c
//  Part2
//
//  Created by jr2339 on 2/14/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "bitarray.h"

void bitArray_init(char* array,int array_size){
    memset(array, 0, array_size);
}


void bitArray_setbit(char*array, long DNA_Number){
    //CHAR_BIT is 8 in our OS
    
    int index = (int)(DNA_Number / CHAR_BIT);
    
    int off_set = (int)(DNA_Number % CHAR_BIT);
    
    unsigned char shift = 0x80u >> off_set;
    
    array[index] |= shift;
    
}



