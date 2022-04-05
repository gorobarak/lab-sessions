#include <stdio.h>
#include <stdlib.h>

int main(){
    int iarray[3];
    float farray[3];
    double darray[3];
    char carray[3];
    int* iarrayPlus = iarray+1;
    float* farrayPlus = farray+1;
    double* darrayPlus = darray+1;
    char* carrayPlus = carray+1;

    
    printf("- &iarray: %p\n",&iarray);
    printf("- &iarray+1: %p\n",&(iarrayPlus));
    printf("- &farray: %p\n",&(farray));
    printf("- &farray+1: %p\n",&(farrayPlus));
    printf("- &darray: %p\n",&(darray));
    printf("- &darray+1: %p\n",&(darrayPlus));
    printf("- &carray: %p\n",&(carray));
    printf("- &carray+1: %p\n",&(carrayPlus));
    


    return 0;
}
