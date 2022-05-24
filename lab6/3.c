#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "LineParser.h"

#define MAX_SIZE 2048

#define STDIN 0
#define STDOUT 1

int debug = 0;

int ** createPipes(int nPipes){
    int** pipes;
    pipes=(int**) calloc(nPipes, sizeof(int));

    for (int i=0; i<nPipes;i++){
        pipes[i]=(int*) calloc(2, sizeof(int));
        pipe(pipes[i]);
    }  
    return pipes;

    }
void releasePipes(int **pipes, int nPipes){
        for (int i=0; i<nPipes;i++){
            free(pipes[i]);
        
        }  
    free(pipes);
}
int *leftPipe(int **pipes, cmdLine *pCmdLine){
    if (pCmdLine->idx == 0) return NULL;
    return pipes[pCmdLine->idx -1];
}
int *rightPipe(int **pipes, cmdLine *pCmdLine){
    if (pCmdLine->next == NULL) return NULL;
    return pipes[pCmdLine->idx];
}

int sizeOfList(cmdLine* head)
{
    int count  = 0;
    while(head != NULL)
    {
        head = head->next;
        count++;
    }
    return count;
}

void executeProc(cmdLine* pCmdLine)
{
    int ret_code = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
    if (ret_code == -1)
    {
        perror("execv faield");
        exit(1);
    }
}

void execute(cmdLine* pCmdLine)
{
    
    /* non executable commands */
    if (strcmp(pCmdLine->arguments[0], "quit") == 0)
    {
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


   
    int next = (pCmdLine->next) ? 1 : 0;
    int** pipes;
    int n = sizeOfList(pCmdLine);
    if(next)
    {
        pipes = createPipes(n - 1); 
    }

    pid_t pid = fork();


    if (pid == -1){
        perror("fork faield");
        exit(1);
    }
    else if (pid == 0)
    {
        /*Handle redircet*/
        if (pCmdLine->inputRedirect)
        {
            close(STDIN);
            open(pCmdLine->inputRedirect, O_RDONLY);
        }
        if (pCmdLine->outputRedirect)
        {
            close(STDOUT);
            open(pCmdLine->outputRedirect, O_WRONLY | O_CREAT);
        }
        if(next)
        {
            close(STDOUT);
            dup(pipes[0][1]);
            close(pipes[0][1]);
            executeProc(pCmdLine);
        }
        else
        {
            executeProc(pCmdLine);
        }
    }
    else{ //parent
        if (pCmdLine->blocking == 1)
        {
            waitpid(pid, NULL, 0);
        }

        pid_t running_pid;
        int currpipe = 0;

        while(pCmdLine->next && pCmdLine->next->next)
        {
            close(pipes[currpipe][1]);
            running_pid = fork();
            pCmdLine = pCmdLine->next;
            if(!running_pid) //child
            {
                close(STDIN);
                dup(pipes[currpipe][0]);
                close(pipes[currpipe][0]);
                
                close(STDOUT);
                dup(pipes[currpipe + 1][1]);
                close(pipes[currpipe + 1][1]);

                executeProc(pCmdLine);

            }
            else//parent
            {   
                if (pCmdLine->blocking == 1)
                {
                   waitpid(running_pid, NULL, 0);
                }
                close(pipes[currpipe][0]);
                currpipe++;


            }
        }
        if(next)//handle last cmd in cmd list
        {
            pid_t pid1 = fork();
            pCmdLine = pCmdLine -> next;
            close(pipes[currpipe][1]);
            if (!pid1)
            {
                close(STDIN);
                dup(pipes[currpipe][0]);
                close(pipes[currpipe][0]);
                executeProc(pCmdLine);
            }
            else
            {
                if (pCmdLine->blocking == 1)
                {
                   waitpid(running_pid, NULL, 0);
                }
                close(pipes[currpipe][0]);
            }
            
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
        printf("-*- %s -*- %%",path);

        fgets(user_input, MAX_SIZE, stdin);      
        
        cmdLine = parseCmdLines(user_input);
        execute(cmdLine);
        freeCmdLines(cmdLine);
    }
    return 0;
}

