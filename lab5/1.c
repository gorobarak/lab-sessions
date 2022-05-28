#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

#include "LineParser.h"

#define MAX_SIZE 2048
int debug = 0;

void execute(cmdLine* pCmdLine)
{
    
    /*Handle shell commands*/
    if (strcmp(pCmdLine->arguments[0], "quit") == 0)
    {
        freeCmdLines(pCmdLine);
        exit(0);
    }
    else if (strcmp(pCmdLine->arguments[0], "cd") == 0)
    {
        int ret = chdir(pCmdLine->arguments[1]);
        if (ret == -1)
        {
            perror("change dir failed");
            exit(1);
        }
        return;
    }
    
    pid_t pid = fork();
    if (pid == -1){
        perror("fork faield");
        exit(1);
    }

    else if (pid == 0) //child
    {

        int ret_code = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        if (ret_code == -1)
        {
            perror("execv faield");
            exit(1);
        }   
    }
    else{ //parent
        if (pCmdLine->blocking){
            waitpid(pid, NULL, 0);
        }
        if (debug)
        {
            fprintf(stderr, "pid - %d\ncommand - %s\n", pid, pCmdLine->arguments[0]);
        }
    } 
}

int main(int argc, char* argv[])
{
    char path[PATH_MAX];
    char user_input[MAX_SIZE];
    cmdLine* cmdLine;
    

    if (argc == 2 && strcmp(argv[1], "-d") == 0)
    {
        debug = 1;
    }
    

    while(1)
    {
        getcwd(path, PATH_MAX);
        printf("+++%s+++ %%",path);

        fgets(user_input, MAX_SIZE, stdin);      
        
        cmdLine = parseCmdLines(user_input);
        execute(cmdLine);
        freeCmdLines(cmdLine);
    }
    return 0;
}



