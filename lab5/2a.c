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
    //process_list = &new_process;
    *process_list =  new_process;
}

//<process id> <the command> <process status>
void print_process(process* p){
    printf("%d %s %s\n", p->pid, p->cmd->arguments[0], p->status);
}

void printProcessList(process** process_list)
{
    process* curr = *(process_list);
    while (curr != NULL){
        print_process(curr);
        curr = curr->next;
    }
}