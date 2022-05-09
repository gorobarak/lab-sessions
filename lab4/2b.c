#include "util.h"

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define	O_CREAT		200		/* create if nonexistant */
#define	O_EXCL		800		/* error if already exists */

#define SEEK_SET 00
#define EOF 0
#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define SYS_EXIT 1 //or 55?
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define SYS_GETDENTS 141


typedef struct entry{
  int inode;
  int offset;
  short len; 
  char buff[1];
}entry;

int main (int argc, char* argv[])
{
    int debug = 0;
    int prefixMode = 0;
    char* prefix;
    int maxSize = 8192;
    char* currDir = ".";
    int i;

    char dirData[maxSize];
    int dirFD = system_call(SYS_OPEN, currDir, O_RDONLY, 0777);
    int dirSize = system_call(SYS_GETDENTS, dirFD, dirData, maxSize);

    for (i = 1; i < argc; i++){
        if(strcmp(argv[i],"-D") == 0)
        {
            debug = 1;
        }
        else if (strncmp(argv[i], "-i", 2) == 0)
        {
            prefix = argv[i] + 2;
            prefixMode = 1;
        }
        
    }

    system_call(SYS_WRITE, STDOUT, "something...\n", 13);

    i = 0;
    entry* e;
    while (i < dirSize)
    {
        e = (entry*)(dirData + i);
        system_call(SYS_WRITE, STDOUT, e->buff, strlen(e->buff));
        system_call(SYS_WRITE, STDOUT, "\n", 1);
        
        if (debug)
        {
            system_call(SYS_WRITE, STDERR, "file length - ", 14);
            system_call(SYS_WRITE, STDERR, itoa((int)e->len), sizeof(short));
            system_call(SYS_WRITE, STDERR, "\n\n", 2);
        }
        
        i += e->len;
    }

    return 0;
}