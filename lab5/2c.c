#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

#include "LineParser.h"



#define MAX_SIZE 2048
#define TERMINATED -1
#define RUNNING 1
#define SUSPENDED 0


int count_ids = 0; 
int debug = 0;

typedef struct process{
    cmdLine* cmd; /* the parsed command line*/
    pid_t pid; /* the process id that is running the command*/
    int status; /* status of the process:   RUNNING/SUSPENDED/TERMINATED */
    struct process *next; /* next process in chain */
    int id;
    
} process;
process* process_list = NULL;

process* create_process(cmdLine* cmd, pid_t pid, int status, process* next){
    process* p =  (process*)malloc(sizeof(process));
    p->cmd = cmd;
    p->pid = pid;
    p->status = status;
    p->next = next;
    p->id = ++count_ids;
    return p;
}

void addProcess(process** process_list, cmdLine* cmd, pid_t pid)
{
    process* new_process;
    if (process_list)
    {
        process* head = *(process_list);
        new_process = create_process(cmd, pid, RUNNING, head);
    }
    else
    {
        new_process = create_process(cmd, pid, RUNNING, NULL);
    }
    *(process_list) = new_process;
}

//<process id> <the command> <process status>
void print_process(process* p){
    printf("%d %s %d\n", p->pid, p->cmd->arguments[0], p->status);
}

void updateProcessList(process **process_list)
{
    int status;
    process* curr = *(process_list);
    while(curr != NULL)
    {
        waitpid(curr->pid, &status, WUNTRACED);
         if (WIFEXITED(status))
         {
             curr->status = TERMINATED;
         }
         else if (WIFSTOPPED(status))
         {
             curr->status = SUSPENDED;
         }
    }
}

void printProcessList(process** process_list)
{
    printf("entered printProcess");
    updateProcessList(process_list);
    printf("print after update");
    process* prev = NULL;
    process* curr = *(process_list);
    printf("PID  CMD  STATUS");
    while (curr != NULL){
        printf("print inside loop");
        print_process(curr);
        if(curr->status == TERMINATED)
        {
            prev->next = curr->next;
            //free here
        }
        else{
            prev = curr; 
        }
        
        curr = curr->next;
        
    }
}

void freeProcessList(process** process_list)
{
    process* curr = *(process_list);
    while (curr != NULL)
    {
        process* tmp = curr;
        curr = curr->next;
        freeCmdLines(tmp->cmd);
        free(tmp);
        
    } 
    
}

void updateProcessStatus(process** process_list, int pid, int status)


{
    process* curr = *(process_list);
    while(curr != NULL && curr->pid != pid)
    {
        curr = curr->next;
    }
    if (curr != NULL)
    {
        curr->status = status;
    }
}

void execute(cmdLine* pCmdLine)
{
    // printf("COMMAND IS: ", pCmdLine->arguments[0]);
    pid_t pid = fork();
    if (pid == -1){
        perror("fork faield");
        exit(1);
    }
    else if (pid == 0) //child
    {
        printf("pid is - %d", pid);
        if (strcmp(pCmdLine->arguments[0],"nap") ==0 )
        {
            kill(atoi(pCmdLine->arguments[2]), SIGTSTP);
            sleep(atoi(pCmdLine->arguments[1]));
            kill(atoi(pCmdLine->arguments[2]), SIGCONT);
            exit(0);
        }
        else if(strcmp(pCmdLine->arguments[0],"sleep") == 0 )
        {
            kill(atoi(pCmdLine->arguments[1]), SIGINT);
            exit(0);
        }
        // else if (strcmp(pCmdLine->arguments[0],"showprocs") == 0)
        // {
        //     printProcessList(&(process_list));
        //     exit(0);
        // }
        else //perform regular cmd
        {
            int ret_code = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
            if (ret_code == -1)
            {
                perror("execv faield");
                exit(1);
            } 
        }
          
    }
    else{ //parent
        if (pCmdLine->blocking == 1){
            waitpid(pid, NULL, 0);
        }
        if (debug)
        {
            fprintf(stderr, "pid - %d\ncommand - %s\n", pid, pCmdLine->arguments[0]);
        }
        addProcess(&(process_list), pCmdLine, pid);
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
        printf("%s %%",path);

        fgets(user_input, MAX_SIZE, stdin);
        if (strcmp(user_input, "quit\n") == 0)
        {
            
            exit(0);
        }
        else if (strncmp("cd ", user_input, 3) == 0)
        {
            char* path = user_input + 3;
            path[strlen(path) -1]  = '\0';

            int ret = chdir(path);
            if (ret == -1)
            {
                perror("change dir failed");
                exit(1);
            }
            continue;
        }
        
        printf("before parse\n");
        cmdLine = parseCmdLines(user_input);
        printf("cmdline - %s", cmdLine->arguments[0]);
        if (strcmp(cmdLine->arguments[0],"showprocs") == 0)
        {
            printProcessList(&(process_list));
            exit(0);
        }
        execute(cmdLine);
        //freeCmdLines(cmdLine);
    }
    return 0;
}