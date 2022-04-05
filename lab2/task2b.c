#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char encrypt(char c){
    if(0x41 <= c && c <= 0x7a){
        return c + 2;
    }
    else{
        return c;
    }
}

char decrypt(char c){
    if(0x41 <= c && c <= 0x7a){
        return c - 2;
    }
    else{
        return c;
    }
}

char dprt(char c){
    printf("%d\n", c);
    return c;
}

char cprt(char c){
    if(0x41 <= c && c <= 0x7a){
        int v = c;

        printf("%c\n", v);//????
        printf("Hello 1\n");
    }
    else{
        printf("*\n");
        printf("Hello 2\n");
    }
    return c;
}

char my_get(char c){
    char ch =fgetc(stdin);
    fputc(ch,stdout);
    return c;
}


// int main(){
//     printf("%c",cprt('a'));
//     return 0;
// }