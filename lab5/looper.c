#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handler(int signum) {
	char* signame = strsignal(signum);
	
	if (signum == SIGTSTP)
	{
		signal(SIGCONT, handler);
	}
	else if (signum == SIGCONT)
	{
		signal(SIGTSTP, handler);
	
	}
	
	printf("received signal: %s\n", signame);
	signal(signum, SIG_DFL);
	raise(signum);

}



int main(int argc, char **argv){ 
	signal(SIGINT , handler);
	signal(SIGCONT , handler);
	signal(SIGTSTP , handler);

	printf("Starting the program\n");

	while(1) {
		sleep(2);
	}

	return 0;
}