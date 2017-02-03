//
//  main.c
//  Part1
//
//  Created by jr2339 on 2/3/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 2000000000


void read_save_file(const char* filename,char* buffer,char* result){
    int count = 0;
    
  
    
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        fprintf(stderr, "can't open file for reading\n");
        exit(1);
    }
    
    while(1){
        //skip the headers
        int ch = getc(fp);
        while (ch == '>') {
            do{
                ch = getc(fp);
            }
            while (ch!='\n');
            ch = getc(fp);
        }

        if (feof(fp)) {
            break;
        }
        //save the character to buffer
        buffer[count] = ch;
        count++;
    }


    
    
    fclose(fp);
   
}


void sort_file(const char* filename,char* buffer,char* result){
    
    read_save_file(filename,buffer,result);
    
    printf("%s\n",result);
    
    printf("=============================================================\n");
    
    printf("%s\n",result);
    printf("=============================================================\n");
    
    
    
    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc < 2) {
        perror("we need more arguments");
        exit(1);
    }
    else if(argc > 2){
        perror("Too many arguments");
        exit(1);
    }
    const char *input = argv[1]; // input file
    char* buffer = (char*)malloc(MAX_SIZE*sizeof(char));
    char* result;
    result = buffer;

    sort_file(input,buffer,result);
    
    free(buffer);
    
    return 0;
}
