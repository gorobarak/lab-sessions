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

int main (int argc, char* argv[]){
    int debug = 0;
    char* input_file = "stdin";
    char* output_file = "stdout";
    int input_desc = STDIN;
    int output_desc = STDOUT;
    int i;

    for (i = 1; i < argc; i++){
       
        if(strcmp(argv[i],"-D") == 0)
        {
            debug = 1;
        }
        else if (strncmp(argv[i], "-i", 2) == 0)
        {
            input_file = argv[i] + 2;
            input_desc = system_call(SYS_OPEN, input_file, O_RDWR, 0777);/*/one more arg? permissions?
            // if() //try to open
            // {
            //     system_call(SYS_WRITE, STDOUT, "File does not exist or not accessible.");
            //      //add exit
                }
            /*/ 

            system_call(SYS_LSEEK, input_desc, 0, SEEK_SET);

        }
        else if (strncmp(argv[i], "-o", 2) == 0)
        {
            output_file = argv[i] + 2;

            

            output_desc = system_call(SYS_OPEN, output_file, O_RDWR | O_CREAT | O_EXCL, 0777);/*/one more arg? permissions?
            // if() //try to open
            // {
            //     system_call(SYS_WRITE, STDOUT, "File does not exist or not accessible.");
            //      //add exit
            // }*/
            system_call(SYS_LSEEK, output_desc, 0, SEEK_SET);

        }
    }
    if (debug)
    {
        system_call(SYS_WRITE, STDERR,"Input file - ", 13);
        system_call(SYS_WRITE, STDERR, input_file, strlen(input_file));
        system_call(SYS_WRITE, STDERR, "\n", 1);
        system_call(SYS_WRITE, STDERR,"Output file - ", 14);
        system_call(SYS_WRITE, STDERR, output_file, strlen(output_file));
        system_call(SYS_WRITE, STDERR, "\n", 1);
    }
    

    
    int count = 0;
    char c;
    int IN = 0;
    int num_of_bytes_read; 
    
    
    num_of_bytes_read = system_call(SYS_READ, input_desc, &c, 1);
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
            system_call(SYS_WRITE, output_desc, "Count is:",9);
            int num_of_bytes_written = system_call(SYS_WRITE, output_desc, str, strlen(str));
            system_call(SYS_WRITE, output_desc, "\n", 1);
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
        num_of_bytes_read = system_call(SYS_READ, input_desc, &c, 1);
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
    system_call(SYS_WRITE, output_desc, "\n", 1);
    return 0;
}
