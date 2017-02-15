#include "sequence.h"



void number_to_Alphbet(int *a, int n, int j, int index,long* Sequence_Number,char** sequence){
    
    sequence[j] = (char*)malloc((n+1)*sizeof(char));
    long DNA_Radix=0;
    //Sequence_Number[index] =0;
    //Due to 1 int is 4bytes = 4 char
    char* buffer = (char*)malloc(4*n);
    //char rdix[10];
    for(int m = 0; m < n; m++){
        //printf("%d", a[i]);
        sprintf(buffer+4*m,"%d",a[m] );
        //printf("%s",buffer);
        DNA_Radix += a[n-m-1]*pow(4, m);
    }
    
    //sprintf(rdix, "%ld", DNA_Radix);
    //convert number to 'ACGT'
    for (int k=0; k<4*n; k+=4) {
        //printf("%c",*(buffer+k));
        if (*(buffer+k)=='0') {
            *(sequence[j]+(k/4)) ='A';
        }
        else if(*(buffer+k)=='1'){
            *(sequence[j]+(k/4)) ='C';
        }
        else if(*(buffer+k)=='2'){
            *(sequence[j]+(k/4)) ='G';
        }
        else if(*(buffer+k)=='3'){
            *(sequence[j]+(k/4)) ='T';
        }
        else{
            *(sequence[j]+(k/4)) ='\0';
        }
    }
    printf("---->%s",sequence[j]);
    Sequence_Number[index] = DNA_Radix;
    printf("--->%ld\n",Sequence_Number[index]);
    index++;
    j++;
    
}

long* gen_all_sequences(int col,long* Sequence_Number){
    /*We have 'ACGT, whcih size is 4*/
  
    //long DNA_Sequence_Number_Size = pow(4, col);
    //Sequence_Number = malloc(DNA_Sequence_Number_Size*sizeof(long));
    int index_Sequence_Number = 0;
    int base_size =4;
    long row = pow(base_size,col);
    
    char** sequence = (char**)malloc(row*sizeof(char*));
    
    int j=0;//increament by col
    
    int i;
    
    int *a;
    //parameter check
    /*
    if(base_size < 2 || col < 1){
        return;
    }*/
    //base_size = max digit value
    base_size -= 1;
    
    a = malloc(col * sizeof(int));
    //start with all zeroes
    for(i = 0; i < col; i++){
        a[i] = 0;
    }
    
    number_to_Alphbet(a,col,j,index_Sequence_Number,Sequence_Number,sequence);
    index_Sequence_Number++;
    
    while(1){
        i = col - 1;
        while(a[i] < base_size){
            a[i]++;
            number_to_Alphbet(a,col,j,index_Sequence_Number,Sequence_Number,sequence);
             index_Sequence_Number++;
        }
        
        while(i >= 0 && a[i] == base_size){
            i--;
        }
        //return if down
        if(i < 0){
            break;
        }
        a[i]++;
        
        //zero following digits
        
        while(++i < col){
            a[i] = 0;
        }
        number_to_Alphbet(a,col,j,index_Sequence_Number,Sequence_Number,sequence);
         index_Sequence_Number++;
    }
    //free(a);
    
    return Sequence_Number;
}







