#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task2b.h"
 
char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}


 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  for (int i = 0; i < array_length; i++){
      mapped_array[i] = f(array[i]);
  }
  return mapped_array;
}

char quit(char c){
    if(c == 'q'){
        exit(0);
    }
    else{
        return c;
    }
}
 
int main(int argc, char **argv){
  int base_len = 5;
  char arr1[base_len];
  char* arr2 = map(arr1, base_len, &my_get);
  char* arr3 = map(arr2, base_len, &encrypt);
  char* arr4 = map(arr3, base_len, &dprt);
  char* arr5 = map(arr4, base_len, &decrypt);
  char* arr6 = map(arr5, base_len, &cprt);
  free(arr2);
  free(arr3);
  free(arr4);
  free(arr5);
  free(arr6);
}