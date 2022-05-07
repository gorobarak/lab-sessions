 #include "util.h"


#define O_RDWR 02
#define SEEK_SET 00

#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19

 int main (int argc, char* argv[]){
    char* pathname = argv[1];
    char* xname = argv[2];
    int file_desc = system_call(SYS_OPEN,pathname, O_RDWR, 0777);
    system_call(SYS_LSEEK, file_desc, 657, SEEK_SET);
    system_call(SYS_WRITE, file_desc, xname, strlen(xname));
    system_call(SYS_CLOSE,file_desc);

    return 0;
 }