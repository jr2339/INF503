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
    
   
    
    long* DNA_Sequence_Number= malloc(DNA_Sequence_Number_Size*sizeof(long));
    
    DNA_Sequence_Number = gen_all_sequences(column,DNA_Sequence_Number);
  
    
    for (int i=0; i<DNA_Sequence_Number_Size; i++) {
        printf("%ld\n",DNA_Sequence_Number[i]);
    }
    
    int bit_Array_size = (int) (DNA_Sequence_Number_Size/8);
   
    char bitArray[bit_Array_size];
    
    bitArray_init(bitArray, bit_Array_size);
    
    
    for (int i=0; i<bit_Array_size; i++) {
        printf("%d in bit array is %x\n",i,bitArray[i]);
    }
    
    for (int i=0; i<DNA_Sequence_Number_Size; i++) {
        bitArray_setbit(bitArray, DNA_Sequence_Number[i]);
    }
    
    printf("================After we set bit array value===============\n");
    for (int i=0; i<bit_Array_size; i++) {
        
        printf("%d in bit array is %d\n",i,((unsigned int)bitArray[i]));
    }
    
    
    return 0;
}
