#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


int debug = 0;
int currentfd = -1;
char* map_start;
off_t size; 


struct fun_desc
{
   char* name;
   void (*f)();
};

void terminate_normaly()
{
    munmap(map_start, size);
    close(currentfd);
    currentfd = -1;
}

void quit(){
    terminate_normaly();
    exit(0);
}
void toggle_debug()
{
    if(debug)
    {       
        debug = 0;
        printf("Debug mode now OFF");
    }
    else
    {
        debug = 1;
        printf("Debug mode now ON");
    }
    return;
}
void examine_elf()
{   
    char filename[1000];
    printf("Please enter ELF file name: ");
    fgets(filename,1000, stdin);
    sscanf(filename, "%s", filename);

    currentfd  = open(filename, O_RDONLY);
    
    if (currentfd == -1)  perror("open file failed");

    size = lseek(currentfd, 0, SEEK_END);
    Elf32_Ehdr *header = mmap(0, size, PROT_READ, MAP_SHARED, currentfd, 0);

    if (!(header->e_ident[0] == 0x7f && header->e_ident[1] == 'E' && header->e_ident[2] == 'L' && header->e_ident[3] == 'F'))
    {
        terminate_normaly();
        exit(1);
    }

    printf("Bytes 1,2,3 of the magic number (in ASCII): ");
    for (int i = 1; i < 4; i++)
        printf("%x ", header->e_ident[i]);
    printf("\n");
    // ----------------------------------------
    printf("The data encoding scheme of the object file: ");
    printf("%u\n", header->e_ident[5]);
    // ----------------------------------------
    printf("Entry point (hexadecimal address): ");
    printf("%p\n", (Elf32_Addr *)(header->e_entry));
    // ----------------------------------------
    printf("The file offset in which the section header table resides: ");
    printf("%u (bytes into file)\n", header->e_shoff);
    // ----------------------------------------
    printf("The number of section header entries: ");
    printf("%d\n", (header->e_shnum));
    // ----------------------------------------
    printf("The size of each section header entry: ");
    printf("%d (bytes)\n", (header->e_shentsize));
    // ----------------------------------------
    printf("The file offset in which the program header table resides: ");
    printf("%u (bytes into file)\n", header->e_phoff);
    // ----------------------------------------
    printf("The number of program header entries: ");
    printf("%d\n", (header->e_phnum));
    // ----------------------------------------
    printf("The size of each program header entry: ");
    printf("%d (bytes)\n", (header->e_phentsize));
    // ----------------------------------------

    

}

void f(){
    printf("Not implemented yet");
    exit(0);    
}

int main(){
    struct fun_desc menu[] = {
        {"Toggle Debug", &toggle_debug},
        {"Examine ELF", &examine_elf},
        {"Print Section", &f},
        {"Print Symbols", &f},
        {"Quit", &quit}
    };
    while(1){
        int len = sizeof(menu) / sizeof(struct fun_desc);
        
        printf("---------------------\nPlease choose a function:\n");
        
        for (int i = 0; i < len ; i++){
            printf("%d) %s\n", i, menu[i].name);
        }
        
        
        int c  = fgetc(stdin);
        fgetc(stdin); // get rid of \n
        c -= '0';
        


        if ( 0 <= c && c <= len -1)
        {
            menu[c].f();
        }
        else{
            printf("Not within bounds\n");
        }
    }
}


