#include "sequence.h"
#include "bitarray.h"

int main(int argc, char **argv)
{
    
    if(argc < 2){
        perror("We need more arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if(argc > 2){
        perror("Too many arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    int column =atoi(argv[1]); // at least 16
    
    long DNA_Sequence_Number_Size = pow(4, column);
    
    //printf("%ld\n",DNA_Sequence_Number_Size);
    
    //int bit_array_size = pow(4, (column-2));
    
    long* DNA_Sequence_Number= malloc(DNA_Sequence_Number_Size*sizeof(long));
    
    DNA_Sequence_Number = gen_all_sequences(column,DNA_Sequence_Number);
    /*
    for (int i=0; i<DNA_Sequence_Number_Size; i++) {
        DNA_Sequence_Number--;
    }
     */
    
    for (int i=0; i<DNA_Sequence_Number_Size; i++) {
        printf("%ld\n",DNA_Sequence_Number[i]);
    }
     
    return 0;
}
