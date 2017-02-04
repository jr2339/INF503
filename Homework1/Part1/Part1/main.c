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

// Function at here to Calcuate the total size we need to reserved.
//At here, i will give a little bigger than we calculated
int count_size(const char* filename){
    int size;
    int col = 0;
    int line = 0;
    
    
    
    FILE *fp = fopen(filename, "r");
    
    if (!fp) {
        fprintf(stderr, "can't open file for reading\n");
        exit(1);
    }
    
    while(1){
        
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
       
        col++;
        if (ch == '\n') {
            line++;
        }
    }
    size = (line +1)*col;
    return size;
    
};





int skip_header(const char* filename,char* buffer){
    int count = 0;
    int line = 0;
    
  
    
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
        if (ch == '\n') {
            line++;
        }
    }

    
    printf("line is %d\n",line);
    
    fclose(fp);
    return line;
   
}



void merge_sort(const char* filename,char* buffer,char** result){
    int line = skip_header(filename,buffer);
    char** left;
    char** right;
    printf("HAHAHAHAHAHAHAHAHA\n");
    for (int i=0; i<line/2+1; i++) {
        **left = **result;
        left++;
        result++;
    }
     printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
    for (int j=0; j<line/2; j++) {
        right[j] = result[line/2+j+1];
    }
    
    printf("%s\n",*left);
    
    printf("=============================================================\n");
    printf("%s\n",*right);
    
    printf("=============================================================\n");
}

void sort_file(const char* filename,char* buffer,char** result){
    
   
    merge_sort(filename,buffer,result);

    

    
    
    
    
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
    
    int size = count_size(input);
    
    char* buffer = (char*)malloc(size*sizeof(char));
    
    char** result;
    result = &buffer;

    sort_file(input,buffer,result);
    
    //printf("%s\n",*result);
    
    //printf("=============================================================\n");
    

    
    free(buffer);
    
    return 0;
}
