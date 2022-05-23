#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 5


int main()
{
    
    int pipe_ends[2];
    pipe(pipe_ends);
    int pid = fork();
    char buf[SIZE]; 

    if (pid == 0)
    {
        dprintf(pipe_ends[1],"hello");
    }
    else
    {
        waitpid(pid, NULL, 0);
        read(pipe_ends[0], buf, SIZE);
        printf("This is parent saying  - %s\n", buf);
    }
    return 0;
}