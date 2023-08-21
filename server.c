#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum)
{
	if (signum == SIGUSR1)
		write(1,"1",1);
	else
		write(1,"0",1);
}


int main ()
{
	pid_t	pid;
	
	pid = getpid();
	printf("pid = [%d]\n",pid);

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1,&sa,NULL);
	sigaction(SIGUSR2,&sa,NULL);
	
	while(1)
	pause();
}
