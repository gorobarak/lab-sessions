#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}

char quit(char c){
    if(c == 'q'){
        exit(0);
    }
    else{
       return c;
    }
}

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

char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  for (int i = 0; i < array_length; i++){
      mapped_array[i] = f(array[i]);
  }
  return mapped_array;
}

