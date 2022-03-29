#include <stdlib.h>
#include <stdio.h>

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
        if ( 64 < ch && ch <91){
            fputc(46,out);// 46 == .
            counter++;
            if(debug){
                fprintf(err, "%i %i", ch,46);
            }
        }
        else{
            fputc(ch,out);
            if(debug){
                fprintf(err,"%i %i", ch,ch);
            }
        }
        ch = fgetc(in);
    }
    if(debug){
        fprintf(err, "the number of letters: %i", counter);
    }
    printf("/n");
    return 0;
}
