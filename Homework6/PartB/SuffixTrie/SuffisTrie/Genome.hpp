//
//  Genome.hpp
//  SuffisTrie
//
//  Created by jr2339 on 4/7/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Genome_hpp
#define Genome_hpp


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
int count_row(const char* filename);
int count_column(const char* filename);
char* get_sequence(int size,const char* filename);
#endif /* Genome_hpp */
