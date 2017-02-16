//
//  bitarray.h
//  Part2
//
//  Created by jr2339 on 2/14/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef bitarray_h
#define bitarray_h
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "sequence.h"


void bitArray_init(char* array,int array_size);

void bitArray_setbit(char*array, long DNA_Number);


#endif /* bitarray_h */
