//
//  main.c
//  Part2
//
//  Created by jr2339 on 2/6/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>



//let's define a linked list node
struct node {
    char val[100];
    struct node * next;
};

//create global node
struct node *head = NULL;



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

//display the list
void printList(int column) {
    struct node *current = head;
    
    
    //start from the beginning
    while(current != NULL) {
        for (int i=0; i<column; i++) {
            printf("%c",current->val[i]);
        }
        
        current = current->next;
    }
    
    
}

//add the DNA Sequence to the linked list
void Insert_To_LinkedList(char* buffer,int row,int column){
    for (int i=0; i<row; i++) {
        //create a link
        struct node *link = (struct node*) malloc(sizeof(struct node));
        for (int j=0; j<column; j++) {
            link->val[j] = buffer[(row-i-1)*column+j];
        }
        link->next = head;
        head = link;
    }

}

//try to sort our Linked List
void sort(int row,int column){
    struct node *current;
    struct node *next;
    int k = row;
    char temp[column];
    
    for (int i=0; i<row-1; i++,k--) {
        current = head;
        next = head->next;
  
        for (int j =1; j<k; j++) {
            if ((strcmp(current->val, next->val))>0) { // it means current->level > next->val;

                for (int col=0; col<column; col++){
                    temp[col] = current->val[col];
                    current->val[col] = next->val[col];
                    next->val[col] = temp[col];
                    
                }
            }
            current = current->next;
            next = next->next;
        }
    }
}




int main(int argc, const char * argv[]) {
    // insert code here...
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
    printf("====================================================\n");
    
   
    Insert_To_LinkedList(buffer,row,col);
    sort(row, col);
    printList(col);

    
    free(buffer);

    return 0;
}
