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

void detect_virus(char *buffer, unsigned int size, link *virus_list){
    virus_list = virus_list->nextVirus; //dummy head
    
    for(int i=0; i < size; i++){
        link* curr = virus_list;
        while(curr != NULL){
            if ( memcmp(buffer + i, curr->vir->sig, curr->vir->SigSize) == 0){
                printf("The starting byte location in the suspected file: %d\nThe virus name: %s\nThe size of the virus signature: %d \n\n" ,i, curr->vir->virusName, curr->vir->SigSize );
            }
        curr = curr->nextVirus; 
        }
    }
}

void detect_virus_menu(link* virus_list){
    char* filename = (char*)malloc(1000);
    printf("Please enter suspiscious filename\n");
    fgets(filename, 1000, stdin);
    filename[strlen(filename) - 1] = '\0'; //removing \n
    FILE* input = fopen(filename, "r");
    fseek(input, 0, SEEK_END);
    int buffSize = ftell(input);
    rewind(input);
    buffSize = buffSize > 10000 ? 10000 : buffSize;
    char buffer[buffSize];
    fread(buffer, sizeof(char), buffSize, input);
    detect_virus(buffer, buffSize, virus_list);
    free(filename);
    fclose(input);
}

void kill_virus(char *fileName, int signatureOffset, int signatureSize)
{
    FILE* input = fopen(fileName, "r+");
    fseek(input, signatureOffset, SEEK_SET);
    char nop = 0x90;
    for(int i = 0; i < signatureSize; i++)
    {
        fwrite(&nop,1,1,input);
    }
    fclose(input);
}

void fix_file(link* virus_list)
{
    printf("Please enter infected file name:\n");
    char filename[100];
    fgets(filename,100,stdin);
    sscanf(filename,"%s",filename);

    printf("Please enter starting byte location:\n");
    char byteLocation[100];
    fgets(byteLocation,100,stdin);
    int signatureOffset;
    sscanf(byteLocation,"%d",&signatureOffset);

    printf("Please enter the virus sig size:\n");
    char virusSize[100];
    fgets(virusSize,100,stdin);
    int signatureSize;
    sscanf(virusSize,"%d",&signatureSize);

    kill_virus(filename, signatureOffset, signatureSize);
}

void print_90(link *virus_list, FILE* output)
{
    link* curr = virus_list;
    while (curr != NULL)
    {
        virus* vir = curr->vir;
        if(vir->SigSize>90)
        {
            printVirus(vir, output);
        }
        curr = curr->nextVirus;
    }
}

void print_sigs_90_menu(link *virus_list)
{
    if (loaded) print_90(virus_list->nextVirus, stdout); //dummy head effect
}


int main(int argc, char** argv)
{
    loaded = 0;
    fun_desc functions[] =  {{"Load signatures", &load_signatures},
                            {"Print signatures", &list_print_out},
                            {"Detect viruses", &detect_virus_menu},
                            {"Fix file", &fix_file},
                            {"Print signatures >= 90", &print_sigs_90_menu},
                            {"Quit", &quit},
                            {NULL,NULL}};

    link* vlist = (link*)calloc(1,sizeof(link)); // dummy head!! uninitialised data
    int len = sizeof(functions) / sizeof(functions[0]);
    while (1)
    {
        printf("Choose a function:\n");
        for (size_t i = 0; i < len - 1; i++)
        {
            printf("%d) %s\n", i + 1, functions[i].name);
        }
        char c = fgetc(stdin);
        c -= '0';
        fgetc(stdin);//ignore '\n'

        if (c > 0 && c < len)
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
     