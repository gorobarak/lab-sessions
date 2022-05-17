#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "LineParser.h"


#define TERMINATED -1
#define RUNNING 1
#define SUSPENDED 0


typedef struct process{
    cmdLine* cmd; /* the parsed command line*/
    pid_t pid; /* the process id that is running the command*/
    int status; /* status of the process:   RUNNING/SUSPENDED/TERMINATED */
    struct process *next; /* next process in chain */
} process;

void addProcess(process** process_list, cmdLine* cmd, pid_t pid)
{
    process* new_process = (process *)malloc 
    p 
    
    curr->next = new_process;
}