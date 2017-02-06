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
void sort_file(const char* filename,char* buffer,int column,int row,int size){
   
    //char *sorted_array = no_header_array;
    
    char temp[column];
    
    for (int i=0; i<row-1; i++) {
        if (buffer[i*column] > buffer[(i+1)*column]) {
            for (int j=0; j<column; j++) {
                temp[j] =buffer[i*column+j];
                buffer[i*column+j]=buffer[(i+1)*column+j];
                buffer[(i+1)*column+j] = temp[j];
            }
        }
  
    
    }
    /*
    for (int i=0; i<column; i++) {
        for (int j=0; j< row-1; j++) {
            if (buffer[j*column+i] > buffer[(j+1)*column+i]) {
                for (int m=0; m<column; m++) {
                    temp[m] =buffer[j*column+m];
                    buffer[j*column+m]=buffer[(j+1)*column+m];
                    buffer[(j+1)*column+m] = temp[m];
                }

            }
        }
    }*/
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
    printf("%c\n",buffer[0]);
    printf("%c\n",buffer[1*col]);
    printf("%c\n",buffer[2*col]);
    
    
    sort_file(input,buffer,col,row,size);
    
   
    

    
    free(buffer);
    
    return 0;
}
