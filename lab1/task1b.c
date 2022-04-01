#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    FILE* in = stdin;
    FILE* out = stdout;
    FILE* err = stderr;
    int debug = 0;
    int i;
    int counter = 0;
    for(i = 1; i < argc; i++){
        if (strcmp("-D", argv[i]) == 0){
            debug = 1;
        }
        else{
            printf("Invalid Parameters -%s\n", argv[i]);
            return 1; //error
        }
    }

    int ch = fgetc(in);
    while(ch != EOF){
        int b = ch;
        if ( 64 < ch && ch <91){ //is ch uppercase?
            counter++;
            b = 46;
        }
        if(debug){ //output to err, ch before and after conversion
            if(ch != 10){
                fprintf(err,"%i %i\n",ch,b);
            }
            else{
                fprintf(err, "the number of letters converted: %i\n", counter);
            }
            
        }
        fputc(b,out);
        ch = fgetc(in);
    }
    
    printf("\n");
    return 0;
}
