#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    unsigned char* sig;
    char virusName[16];
}virus;

typedef struct link link;

struct link {
    link *nextVirus;
    virus *vir;
};

typedef struct fun_desc{
    char *name;
    void (*fun)(char);
} fun_desc;

void printVirus(virus* vir, FILE* output){
    fprintf(output, "Virus name: %s\n", vir->virusName);
    fprintf(output, "Virus size: %d\n", vir->SigSize);
    fprintf(output, "signature:\n");
    fprintHex(output, vir->sig, vir->SigSize);
}

/* Print the data of every link in list to the given stream. Each item followed by a newline character. */
void list_print(link *virus_list, FILE* output)
{
    link* curr = virus_list;
    while (curr != NULL)
    {
        virus* vir = curr->vir;
        printVirus(vir, output);
        curr = curr->nextVirus;
    }
}
     
/* Add the given link to the list 
        (either at the end or the beginning, depending on what your TA tells you),
        and return a pointer to the list (i.e., the first link in the list).
        If the list is null - return the given entry. */
link* list_append(link* virus_list, link* to_add)
{
    //append
    link* curr = virus_list;
    while (curr->nextVirus != NULL)
    {
        curr = curr->nextVirus;
    }

    curr->nextVirus = to_add;
    return virus_list;

    //prepend
    // to_add->nextVirus = virus_list;
    // return to_add;
}
     
/* Free the memory allocated by the list. */
void list_free(link *virus_list)
{
    while (virus_list != NULL)
    {
        link* t = virus_list;
        virus_list = virus_list->nextVirus;
        free(t->vir->sig);
        free(t->vir);
        free(t);
    }
}

void quit(link* virus_list)
{
    list_free(virus_list);
    exit(0);
}

void load_signatures(link* virus_list)
{
    char* file;
    virus* vir;
    fgets(file, 1000, stdin);
    FILE* input = fopen(file, "r");
    fseek(input, 0, SEEK_END);
    int endOfFile = ftell(input);
    rewind(input);
    int curr = 0;

    while (curr < endOfFile)
    {

        /* code */
    }
    

    
}


int main(int argc, char** argv)
{
    fun_desc functions[] =  {{"Load signatures", load_signatures},
                            {"Print signatures", list_print},
                            {"Quit", quit},
                            {NULL,NULL}};

    while (1)
    {
        printf("Choose a function:");
        for (size_t i = 0; i < 3; i++)
        {
            printf("%d) %s\n", i + 1, functions[i].name);
        }
        char c = fgetc(stdin);
        c -= '0';

        if (c == 1)
        {
            /* code */
        }
        


        

    }
}
     