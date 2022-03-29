#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    FILE* in = stdin;
    FILE* out = stdout;
    int ch = fgetc(in);
    while(ch != EOF){
        if ( 64 < ch && ch <91){
            fputc(46,out);// 46 == .
        }
        else{
            fputc(ch,out);
        }
        ch = fgetc(in);
    }
    printf("/n");
    return 0;
}