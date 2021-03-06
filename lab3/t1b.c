#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loaded;

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
    void (*fun)(link*);
} fun_desc;


void readVirus(virus* vir, FILE* input){
    
    unsigned short SigSize;
    fread(&SigSize, sizeof(short), 1, input);
    vir->sig = malloc(SigSize);
    fread(vir->sig, sizeof(char), SigSize, input);
    fread(vir->virusName,sizeof(char), 16, input);
    vir->SigSize = SigSize;
    
}


void fprintHex(FILE* output, unsigned char* buffer, long length){
    for(int i = 0; i<length; i++){
        fprintf(output ,"%02hhX ", buffer[i]);
    }
    fprintf(output, "\n");
}

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

void list_print_out(link *virus_list)
{
    if (loaded) list_print(virus_list->nextVirus, stdout); //dummy head effect
}
     
/* Add the given link to the list 
        (either at the end or the beginning, depending on what your TA tells you),
        and return a pointer to the list (i.e., the first link in the list).
        If the list is null - return the given entry. */
link* list_append(link* virus_list, link* to_add)
{
    if(virus_list == NULL){
        return to_add;
    }
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
    list_free(virus_list->nextVirus);//dummy head effect?
    free(virus_list);
    exit(0);
}

void load_signatures(link* virus_list)
{
    char* file = (char*)malloc(1000);
    virus* vir;
    printf("Please enter input file name:\n");
    fgets(file, 1000, stdin);
    file[strlen(file) - 1] = '\0';
    FILE* input = fopen(file, "r");
    fseek(input, 0, SEEK_END);
    int endOfFile = ftell(input);
    rewind(input);
    int curr = 0;

    while (curr < endOfFile)
    {
        vir = calloc(1, sizeof(virus));
        readVirus(vir, input);
        link* to_add = (link*)malloc(sizeof(link));
        to_add->nextVirus = NULL;
        to_add->vir = vir;

        virus_list = list_append(virus_list, to_add);
        curr = ftell(input);
    }
    loaded = 1;
    free(file);
    fclose(input);
}


int main(int argc, char** argv)
{
    loaded = 0;
    fun_desc functions[] =  {{"Load signatures", &load_signatures},
                            {"Print signatures", &list_print_out},
                            {"Quit", &quit},
                            {NULL,NULL}};

    link* vlist = (link*)calloc(1,sizeof(link)); // dummy head!! uninitialised data

    while (1)
    {
        printf("Choose a function:\n");
        for (size_t i = 0; i < 3; i++)
        {
            printf("%d) %s\n", i + 1, functions[i].name);
        }
        char c = fgetc(stdin);
        c -= '0';
        fgetc(stdin);//ignore '\n'

        if (c > 0 && c < 4)
        {
            functions[c - 1].fun(vlist);
        }
        else
        {
            printf("not an option\n");
            exit(1);
        }
    }

}
     