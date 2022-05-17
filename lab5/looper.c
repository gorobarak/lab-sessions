#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handler(int sig)
{
	printf("sig: %s", strsignal(sig));
	if (SIGTSTP)
	{
		signal(SIGCONT, handler);
	}
	else if (SIGCONT)
	{
		signal(SIGTSTP, handler);
	}
	signal(sig, SIG_DFL);
	raise(sig);
}

int main(int argc, char **argv){ 

	printf("Starting the program\n");

	while(1) {
		sleep(2);
	}

	return 0;
}