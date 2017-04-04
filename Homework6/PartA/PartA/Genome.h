//
//  Genome.h
//  PartA
//
//  Created by jr2339 on 4/1/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Genome_h
#define Genome_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
int count_row(const char* filename);
int count_column(const char* filename);
char** get_sequence(int number, int size,const char* filename);

#endif /* Genome_h */
