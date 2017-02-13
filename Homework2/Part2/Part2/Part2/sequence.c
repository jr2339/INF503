//
//  sequence.c
//  Part2
//
//  Created by jr2339 on 2/12/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "sequence.h"

void generate_sequence(char str[], char new_str[], int current_len, int n, int len){
    
    if (current_len == len) {//print string when lenght is equal to p
        printf("%s\n",new_str);
        return;
    }
    else{
        for (int i=0; i<n; i++) {
            new_str[current_len] = str[i];
            generate_sequence(str,new_str,current_len+1,n,len);
        }
    }
}
