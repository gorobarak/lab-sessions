#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "LineParser.h"


#define TERMINATED -1
#define RUNNING 1
#define SUSPENDED 0


int count_ids = 0; 
typedef struct node
{
    int data;
    struct node* next;
}node;

typedef struct process{
    cmdLine* cmd; /* the parsed command line*/
    pid_t pid; /* the process id that is running the command*/
    int status; /* status of the process:   RUNNING/SUSPENDED/TERMINATED */
    struct process *next; /* next process in chain */
    int id;
    
} process;

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
    process* head = *(process_list);
    process* new_process = create_process(cmd, pid, RUNNING, head);
    *(process_list) = new_process;
}

//<process id> <the command> <process status>
void print_process(process* p){
    printf("%d %s %s\n", p->pid, p->cmd->arguments[0], p->status);
}

void printProcessList(process** process_list)
{
    updateProcessList(process_list);
    process* prev = NULL;
    process* curr = *(process_list);
    while (curr != NULL){
        print_process(curr);
        if(curr->status == TERMINATED)
        {
            prev->next = curr->next;
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