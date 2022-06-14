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
void* map_start;
off_t size; 
Elf32_Ehdr* header;


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
        printf("Debug mode now OFF\n");
    }
    else
    {
        debug = 1;
        printf("Debug mode now ON\n");
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
    map_start = mmap(0, size, PROT_READ, MAP_SHARED, currentfd, 0);
    header = (Elf32_Ehdr*) map_start;

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

void print_section_names()
{
    if (currentfd == -1)
    {
        printf("No ELF File loaded\n");
        exit(1);
    }


    Elf32_Shdr* section_header = (Elf32_Shdr *)(map_start + header->e_shoff);
    int num_of_sections = header->e_shnum;
    Elf32_Shdr *sh_strtab = &section_header[header->e_shstrndx];
    const char *const sh_strtab_p = map_start + sh_strtab->sh_offset;

    printf("[Nr] Name                 Addr     Off      Size     Type\n");
    for (int i = 0; i < num_of_sections; ++i)
    {
        const char *section_name = sh_strtab_p + section_header[i].sh_name;
        Elf32_Addr addr = section_header[i].sh_addr;
        Elf32_Off offset = section_header[i].sh_offset;
        Elf32_Word size = section_header[i].sh_size;
        Elf32_Word type = section_header[i].sh_type;

        printf("[%-2d] %-20s %08x %08x %08x %-u\n", i, section_name, addr, offset, size, type);
    }
    if(debug)
    {
        printf("shstrndx is = %d\n",header->e_shstrndx);
    }
}

void print_symbols()
{
    Elf32_Shdr *section_header = (Elf32_Shdr *)(map_start + header->e_shoff); //section header table
    int num_of_sections = header->e_shnum; 
    char *section_names = (char *)(map_start + section_header[header->e_shstrndx].sh_offset); //start of section header string table (offset is absoulte offset)
    int index = 0;
    printf("Num:    value      section_index section_name symbol_name\n");
    for (int i = 0; i < num_of_sections; i++)
    {
        if (section_header[i].sh_type == SHT_SYMTAB) //Symbol table section
        {
            Elf32_Sym *symtab = (Elf32_Sym *)(map_start + section_header[i].sh_offset);//start of symbol table
            int symbols_num = section_header[i].sh_size / section_header[i].sh_entsize;
            char *symbol_names = (char *)(map_start + section_header[section_header[i].sh_link].sh_offset);
            for (int j = 0; j < symbols_num; j++)
            {
                char *symbol_name = symbol_names + symtab[j].st_name;
                char *section_name = section_names + section_header[i].sh_name;
                printf("%-2d:     %08x   %-12d  %-13s %s\n",
                       index,
                       symtab[j].st_value,
                       symtab[j].st_shndx,
                       section_name, 
                       symbol_name);
                index++;
            }

            if(debug)
            {
                printf("size of symbol table is (num of elements) - %d\n", symbols_num);
            }
        }
    }
}

void print_dymsymbols()
{
    Elf32_Shdr *section_header = (Elf32_Shdr *)(map_start + header->e_shoff); //section header table
    int num_of_sections = header->e_shnum; 
    char *section_names = (char *)(map_start + section_header[header->e_shstrndx].sh_offset); //start of section header string table (offset is absoulte offset)
    int index = 0;
    printf("Num:    value      section_index section_name symbol_name\n");
    for (int i = 0; i < num_of_sections; i++)
    {
        if (section_header[i].sh_type == SHT_DYNSYM) //dynamic Symbol table section
        {
            Elf32_Sym *symtab = (Elf32_Sym *)(map_start + section_header[i].sh_offset);//start of symbol table
            int symbols_num = section_header[i].sh_size / section_header[i].sh_entsize;
            char *symbol_names = (char *)(map_start + section_header[section_header[i].sh_link].sh_offset);
            for (int j = 0; j < symbols_num; j++)
            {
                char *symbol_name = symbol_names + symtab[j].st_name;
                char *section_name = section_names + section_header[i].sh_name;
                printf("%-2d:     %08x   %-12d  %-13s %s\n",
                       index,
                       symtab[j].st_value,
                       symtab[j].st_shndx,
                       section_name, 
                       symbol_name);
                index++;
            }
        }
    }
}

int main(){
    struct fun_desc menu[] = {
        {"Toggle Debug", &toggle_debug},
        {"Examine ELF", &examine_elf},
        {"Print Section Names", &print_section_names},
        {"Print Symbols", &print_symbols},
        {"Print DymSymbols", &print_dymsymbols},
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


