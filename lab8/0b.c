#include <stdlib.h>
#include <stdio.h>
int debug = 0; 

struct fun_desc
{
   char* name;
   void (*f)();
};


void quit(){
    exit(0);
}
void toggle_debug()
{
    if(debug)
    {       
        debug = 0;
        printf("Debug mode now OFF");
    }
    else
    {
        debug = 1;
        printf("Debug mode now ON");
    }
    return;
}
void f(){
    printf("Not implemented yet");
    exit(0);    
}

int main(){
    struct fun_desc menu[] = {
        {"Toggle Debug", &toggle_debug},
        {"Examine ELF", &f},
        {"Print Section", &f},
        {"Print Symbols", &f},
        {"Quit", &quit}
    };
    while(1){
        int len = sizeof(menu) / sizeof(struct fun_desc);
        
        printf("\nPlease choose a function:\n");
        
        for (int i = 0; i < len ; i++){
            printf("%d) %s\n", i, menu[i].name);
        }
        
        printf("Option:");
        
        int c  = fgetc(stdin);
        fgetc(stdin); // get rid of \n
        c -= '0';
        


        if ( 0 <= c && c <= len -1)
        {
            menu[c].f();
        }
        else{
            printf("Not within bounds\n");
        }
    }
}