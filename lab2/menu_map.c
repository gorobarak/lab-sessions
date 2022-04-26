#include <stdlib.h>
#include <stdio.h>
#include "task2b.h"

struct fun_desc
{
   char* name;
   char (*f)(char);
};


int main(){
    int base_len = 5;
    char carray[base_len];
    char* carrayPtr = carray;
    struct fun_desc menu[] = {
        {"Censor", &censor},
        {"Encrypt", &encrypt},
        {"Decrypt", &decrypt},
        {"Print dec", &dprt},
        {"Print string", &cprt},
        {"Get string", &my_get},
        {"Quit", &quit},
        {NULL, NULL}
    };
    while(1){
        int len = sizeof(menu) / sizeof(struct fun_desc);
        
        printf("\nPlease choose a function:\n");
        
        for (int i = 0; i < len -1 ; i++){
            printf("%d) %s\n", i, menu[i].name);
        }
        
        printf("Option:");
        
        char c  = fgetc(stdin);
        fgetc(stdin); // get rid of \n
        c -= '0';
        


        if ( 0 <= c && c <= len -2){
            printf("Within bounds\n");
            char* tmp = map(carrayPtr, base_len, menu[c - 0].f );
            //free(carrayPtr);
            if(c < len - 2){
                carrayPtr = tmp;
            } 
        }
        else{
            printf("Not within bounds\n");
        }
    }
}


