#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>

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


process* plist = NULL;

process* create_process(cmdLine* cmd, pid_t pid, int status, process* next){
    process* p =  (process*)malloc(sizeof(process));
    p->cmd = cmd;
    p->pid = pid;
    p->status = status;
    p->next = next;
    p->id = ++count_ids;
    return p;
}
char* switchStatus(int status)
{
    switch(status)
    {
        case TERMINATED:
            return "TERMINATED";
        case SUSPENDED:
            return "SUSPENDED";
        case RUNNING:
            return "RUNNING";
            break;
        default:
            return "";
    }
}


//<process id> <the command> <process status>
void print_process(process* p){
    char* statusStr;
    if(p)
    {
        statusStr = switchStatus(p->status);
        printf("%d %s %s\n", p->pid, p->cmd->arguments[0], statusStr);
    }
    else
    {
        printf("Printing a NULL process\n");
    }
}

void updateProcessList(process **process_list)
{
    int status;
    int ret;
    process* curr = *process_list;
    while(curr != NULL)
    {
        ret = waitpid(curr->pid, &status, WUNTRACED | WCONTINUED | WNOHANG);
        if (ret != 0){
            if  (WIFSTOPPED(status))
            {
                curr->status = SUSPENDED;
            }
            else if (WIFCONTINUED(status))
            {
                curr->status = RUNNING;
            }
            else
            {
                curr->status = TERMINATED;
            }
        }
        curr = curr->next;
    }

    return;
}

void delete_process(process* p){
    if(p)
    {
        freeCmdLines(p->cmd);
        free(p);
    }
    return;
}

void printProcessList(process** process_list)
{
    updateProcessList(process_list);
    process* prev = NULL;
    process* curr = *process_list;
    process* next;
    printf("PID  CMD  STATUS\n");
    while (curr != NULL){
        print_process(curr);
        if(curr->status == TERMINATED) //delete from list
        {
             
            if(curr == *process_list)//head
            {
               *process_list = curr->next; 
            }
            else
            {
                prev->next = curr->next;
            }
            next = curr->next;
            delete_process(curr);
            
        }
        else{
            prev = curr;
            next = curr->next; 
        }
        
        curr = next;
        
    }
}

//prepend
void addProcess(process** process_list, cmdLine* cmd, pid_t pid)
{
   

    process* new_process;
    new_process = create_process(cmd, pid, RUNNING, *process_list);
    *process_list =  new_process;
    


}

void freeProcessList(process** process_list)
{
    process* curr = *process_list;
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
    process* curr = *process_list;
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
    
    /*Handle shell commands*/
    if (strcmp(pCmdLine->arguments[0], "quit") == 0)
    {
        freeProcessList(&plist);
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
    else if (strcmp(pCmdLine->arguments[0], "showprocs") == 0)
    {
        printProcessList(&plist);
        return;
    }
    else if (strcmp(pCmdLine->arguments[0], "nap") == 0)
    {
        pid_t pid1 = fork();
        if(pid1 == 0)
        {
            pid_t dest_pid = atoi(pCmdLine->arguments[2]);
            kill(dest_pid, SIGTSTP);
            sleep(atoi(pCmdLine->arguments[1]));
            kill(dest_pid, SIGCONT);
            exit(0);
        }
        
        return;
    }
    else if (strcmp(pCmdLine->arguments[0], "stop") == 0)
    {
        pid_t dest_pid = atoi(pCmdLine->arguments[1]);
        kill(dest_pid, SIGINT);
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
        addProcess(&plist, pCmdLine, pid);
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
        
    }
    return 0;
}























