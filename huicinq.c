#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//volatile sig_atomic_t stopwhile=1;
pid_t pid;
void sendsig( __attribute__((unused)) int signo)
{
	if(kill(pid,SIGUSR1) == -1)
	{
		perror("signal");
		exit(1);
	}
}
void traite(__attribute__((unused)) int signo)
{
	write(1,"hello\n",7);
}

void killfils(__attribute__((unused)) int signo)
{

	write(1,"Fils tué \n", 11);
	exit(1);
}
int main(void)
{
	if(signal(SIGALRM,sendsig) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
	if(signal(SIGUSR1,killfils)==SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
	pid=fork();
	switch(pid)
	{
		case -1:
			perror("fork");
			exit(1);
		case 0:
			if(signal(SIGALRM,traite) == SIG_ERR)
			{
				perror("signal");
				exit(1);
			}
			while(1)
			{
				alarm(1);
				pause();
			}
			exit(0);
		default:
			alarm(15);
			pause();
	}
	exit(0);
}
