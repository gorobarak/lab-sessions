#include <stdio.h>
#include <stdlib.h>

int main(){
    int iarray[] = {1,2,3};
    char carray[] = {'a','b','c'};
    int* iarrayPtr = iarray;
    char* carrayPtr = carray;
    void* p;
    for (int i = 0; i < 3; i++)
    {
        printf("iarray - %d\n", *(iarrayPtr+i));
        printf("carray - %c\n",*(carrayPtr+i));
        
    }
    printf("p's address - %p\n",p);
    return 0;
}
