#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

volatile int signum;
volatile sig_atomic_t arret = 0;
int i=0;
pid_t pid;

void send_nude( __attribute__ ((unused)) int signum)
{
    printf("   message %d \n",i);
    i++;
}
void send_nude_2( __attribute__ ((unused)) int signum)
{
    printf("    j'envoie plus de nude");
}
void send_nude_3(__attribute__ ((unused)) int signum)
{
    printf("    fin de la transmission \n");
    if (kill(pid, SIGUSR1) ==-1)
    {
        perror("kill");
        exit(1);
    } 
    arret=1;
    exit(0);
}


int main(void)
{
    int status;
    pid=fork();
    if (signal(SIGALRM, send_nude_2 ) == SIG_ERR)
    {
:q
        perror("signal");
        return -1;
    }
    if (signal(SIGUSR1, send_nude_3) == SIG_ERR)
    {
        perror("signal");
        return -1;
    }
    switch(pid)
    {
        case -1 :
            perror("fork()");
            exit(1);
        case 0 : // fils
            
            if (signal(SIGALRM, send_nude) == SIG_ERR)
            {
                perror("signal");
                return -1;
            }
            
            while(1 && !(arret))
            {
                alarm(1);
                pause();
            }
        default : 
            alarm(60);
            pause();
            if (wait(NULL) ==-1)
            {
                perror("wait");
                return -1;
            }
    }
    return 0;
}
    
