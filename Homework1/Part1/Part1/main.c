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
int count_row(const char* filename){
    int size =0;
    int row = 0;
    
    
    
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
       
        size++;
        if (ch == '\n') {
            row++;
        }
    }

    
    return row;
    
};

int count_col(const char* filename){
    int size =0;
    int row = 0;
    
    
    
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
        
        size++;
        if (ch == '\n') {
            row++;
        }
    }
    
    int col = size/row;
    
    return col;
    
};


//A[i][j] = *(A[i]+j) = *(*(A+i)+j)

void skip_header(const char* filename,char* buffer){
    int size = 0;
    int row = 0;
    
  
    
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
        buffer[size] = ch;
        size++;
        if (ch == '\n') {
            row++;
        }
    }


    
    fclose(fp);

   
}


//A[i][j] = *(A[i]+j) = *(*(A+i)+j)
void sort_file(const char* filename,char* buffer,int column,int row){
    char str1[column];
    char str2[column];
    char temp[column];
    for (int i=0; i<row-1; ++i) {
        for (int j = i+1; j<row; ++j) {
            for (int col=0; col<column; col++) {
                str1[col] = buffer[i*column+col];
                str2[col] = buffer[j*column+col];
            }
            if ((strcmp(str1, str2)>0)) { //str2 less than str1
                for (int m=0; m<column; m++) {
                    temp[m] = buffer[i*column+m];
                    buffer[i*column+m] = buffer[j*column+m];
                    buffer[j*column+m] = temp[m];
                }
            }
        }
    }
     printf("============================================================\n");
     printf("%s\n",buffer);

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
    int row =count_row(input);
    int col =count_col(input);
    int size = row * col;
    printf("the row is %d,the col is %d, the size is %d\n",row,col,size);
    
    char* buffer = (char*)malloc(size*sizeof(char));
    

    
    skip_header(input,buffer);
    
    printf("%s\n",buffer);

    
    
    sort_file(input,buffer,col,row);

    
    free(buffer);
    
    return 0;
}
