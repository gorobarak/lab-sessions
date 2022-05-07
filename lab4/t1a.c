#include "util.h"


#define EOF 0
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19

int main (int argc, char* argv[]){
    int debug = 0;
    int i;
    for (i = 1; i< argc; i++){
        if(strcmp(argv[i],"-D") == 0){
            debug = 1;
        }
    }
    int count = 0;
    char c;
    int IN = 0;
    int num_of_bytes_read; 
    
    
    num_of_bytes_read = system_call(SYS_READ, STDIN, &c, 1);
    if (debug){
        system_call(SYS_WRITE, STDERR,"System call ID excuted:", 23);
        system_call(SYS_WRITE, STDERR,itoa(SYS_READ), strlen(itoa(SYS_READ)));
        system_call(SYS_WRITE, STDERR, "\n", 1);
        system_call(SYS_WRITE, STDERR,"System call return val:", 23);
        system_call(SYS_WRITE, STDERR,itoa(num_of_bytes_read), strlen(itoa(num_of_bytes_read)));
        system_call(SYS_WRITE, STDERR, "\n", 1);
        char str[]  = {c, '\n', '\0'};
        system_call(SYS_WRITE,STDERR, "Current char is:", 16);
        system_call(SYS_WRITE,STDERR, str, 2);
    }
   
    while( num_of_bytes_read != EOF){
        if ( c == ' ' || c == '\n'){
            IN = 0;
        }
        else if(!IN){
            count += 1;
            IN = 1;
        }
        
        if (c == '\n'){
            char* str = itoa(count);
            system_call(SYS_WRITE, STDOUT, "Count is:",9);
            int num_of_bytes_written = system_call(SYS_WRITE, STDOUT, str, strlen(str));
            system_call(SYS_WRITE, STDOUT, "\n", 1);
            count = 0;
            IN = 0;
            if (debug){
                system_call(SYS_WRITE, STDERR,"System call ID excuted:", 23);
                system_call(SYS_WRITE, STDERR,itoa(SYS_WRITE), strlen(itoa(SYS_WRITE)));
                system_call(SYS_WRITE, STDERR, "\n", 1);
                system_call(SYS_WRITE, STDERR,"System call return val:", 23);
                system_call(SYS_WRITE, STDERR,itoa(num_of_bytes_written), strlen(itoa(num_of_bytes_written)));
                system_call(SYS_WRITE, STDERR, "\n", 1);
            }
        }
        num_of_bytes_read = system_call(SYS_READ, STDIN, &c, 1);
        if(debug){
            system_call(SYS_WRITE, STDERR,"System call ID excuted:", 23);
            system_call(SYS_WRITE, STDERR,itoa(SYS_READ), strlen(itoa(SYS_READ)));
            system_call(SYS_WRITE, STDERR, "\n", 1);
            system_call(SYS_WRITE, STDERR,"System call return val:", 23);
            system_call(SYS_WRITE, STDERR,itoa(num_of_bytes_read), strlen(itoa(num_of_bytes_read)));
            system_call(SYS_WRITE, STDERR, "\n", 1);
            char str[]  = {c, '\n', '\0'};
            system_call(SYS_WRITE,STDERR, "Current char is:", 16);
            system_call(SYS_WRITE,STDERR, str, 2);
        }
        
    }
    system_call(SYS_WRITE, STDOUT, "\n", 1);
    return 0;
}
