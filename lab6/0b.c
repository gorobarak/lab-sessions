#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1

int debug = 0;

int main(int argc, char* argv[])
{
    
    if (argc == 2 && strcmp(argv[1], "-d") == 0)
    {
        debug = 1;
    }

    char* ls_args[] = {"ls", "-l", (char*) NULL};
    char* tail_args[] = {"tail", "-n", "2", (char*) NULL};
    // char* debug_str;
    
    int pipe_ends[2];
    pipe(pipe_ends);
    
    if (debug)
    {
        fprintf(stderr, "(parent_process>forking...)\n");
    }
    int pid1 = fork();
    
    
    if (pid1 == 0)
    {
        if (debug)
        {
            fprintf(stderr, "(child1>redirecting stdout to the write end of the pipe:...)\n");
        }

        close(STDOUT); 
        dup(pipe_ends[1]); 
        close(pipe_ends[1]);

        if (debug)
        {
            fprintf(stderr, "(child1>going to execute cmd:...)\n");
        }
        execvp(ls_args[0], ls_args);
    }
    else
    {
        if (debug)
        {
            fprintf(stderr, "(parent_process>created process with id: %d)\n", pid1);
            fprintf(stderr, "(parent_process>closing the write end of the pipe...)\n");
        }
        
        close(pipe_ends[1]);//STEP 4
        int pid2 = fork();
        
        if (pid2 == 0)
        {
            if (debug)
            {
                fprintf(stderr, "(child2>redirecting stdin to the read end of the pipe:...)\n");
            }
            close(STDIN);
            dup(pipe_ends[0]);
            close(pipe_ends[0]);

            if (debug)
            {
                fprintf(stderr, "(child2>going to execute cmd:...)\n");
            }
            execvp(tail_args[0], tail_args);
        }
        else
        {
            if (debug)
            {
                fprintf(stderr, "(parent_process>closing the read end of the pipe...)\n");
            }
            close(pipe_ends[0]);//STEP 7

            if (debug)
            {
                fprintf(stderr, "(parent_process>waiting for the child process to terminate...)\n");
            }
            waitpid(pid1, NULL, 0);//STEP 8
            waitpid(pid2, NULL, 0);//STEP 8
            if (debug)
            {
                fprintf(stderr, "(parent_process>exiting...)\n");
            }
        }
         
    }

    return 0;
}