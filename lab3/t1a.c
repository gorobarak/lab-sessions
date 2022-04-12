#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    unsigned char* sig;
    char virusName[16];
}virus;


void fprintHex(FILE* output, unsigned char* buffer, long length){
    for(int i = 0; i<length; i++){
        fprintf(output ,"%02hhX ", buffer[i]);
    }
    fprintf(output, "\n");
}

void printHex(unsigned char* buffer, long length){
    for(int i = 0; i<length; i++){
        printf("%02hhX ", buffer[i]);
    }
    printf("\n");
    
}

void readVirus(virus* vir, FILE* input){
    unsigned short* SigSize = malloc(sizeof(short));
    fread(SigSize, sizeof(short), 1, input);

    unsigned char* sig = (unsigned char*)malloc((SigSize[0] + SigSize[1]*256)* sizeof(char));
    fread(sig, sizeof(char), (SigSize[0] + SigSize[1]*256), input);

    char name[16];
    fread(name,sizeof(char), 16, input);
    
    vir->SigSize = (SigSize[0] + SigSize[1]*256);

    vir->sig = sig; //ask ralbad
    //strcpy(vir->sig, sig);

    strcpy(vir->virusName, name);


    free(SigSize);
    //free(sig);
    

}

void printVirus(virus* vir, FILE* output){
    fprintf(output, "Virus name: %s\n", vir->virusName);
    fprintf(output, "Virus size: %d\n", vir->SigSize);
    fprintf(output, "signature:\n");
    fprintHex(output, vir->sig, vir->SigSize);
}

int main(int argc, char** argv){
    FILE* input = fopen("signatures", "r");
    virus* vir; 
    fseek(input, 0, SEEK_END);
    int endofFile = ftell(input);
    rewind(input);
    int curr = 0;

    while(curr < endofFile){
        vir = calloc(1, sizeof(virus));
        readVirus(vir, input);
        printVirus(vir, stdout);
        free(vir->sig);
        free(vir);
        curr = ftell(input);

    }
    
    fclose(input);
    printf("\n");
    return 0;
}