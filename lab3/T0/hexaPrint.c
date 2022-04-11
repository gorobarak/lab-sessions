#include <stdio.h>
#include <stdlib.h>

void printHex(unsigned char* buffer, long length){
    for(int i = 0; i<length; i++){
        printf(" %X", buffer[i]);
    }
    
}


int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    unsigned char* buffer = (unsigned char *)calloc(size, sizeof(char));
    fread(buffer, sizeof(char), size, file);

    printHex(buffer, size);

    free(buffer);
    fclose(file);

    printf("\n");
    return 0;
}