//
//  main.c
//  Part2
//
//  Created by jr2339 on 2/12/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        perror("We need more arguments");
        exit(1);
    }
    else if(argc > 2){
        perror("Too many arguments");
    }
    int n = atoi(argv[1]);
    char* sequence = generate_sequence(n);
    
   
    return 0;
}
