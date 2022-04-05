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
 
int main(int argc, char **argv){
  char (*f)(char);
  f = &encrypt;
  char* mapped_array = map(argv[1], strlen(argv[1]), f);
  printf("mapped array - %s\n",mapped_array);
  free(mapped_array);
  /* TODO: Test your code */
}