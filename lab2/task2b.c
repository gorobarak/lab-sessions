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
        printf("%c\n", c);
    }
    else{
        printf("*\n");
    }
    return c;
}

char my_get(char c){
    char ch = fgetc(stdin);
    return ch;
}


