#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "LineParser.h"

#define MAX_SIZE 2048

void execute(cmdLine* pCmdLine)
{
    int ret_code = execv(pCmdLine->arguments[0], pCmdLine->arguments);
    if (ret_code == -1)
    {
        perror("execv faield");
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    char path[PATH_MAX];
    char user_input[MAX_SIZE];
    cmdLine* cmdLine;

    while(1)
    {
        getcwd(path, PATH_MAX);
        printf("%s %%",path);

        fgets(user_input, MAX_SIZE, stdin);
        if (strcmp(user_input, "quit\n") == 0)
        {
            freeCmdLines(cmdLine);
            exit(0);
        }
        cmdLine = parseCmdLines(user_input);
        execute(cmdLine);
    }
    return 0;
}
