#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

int file_in;
volatile sig_atomic_t sign = 0;

void enreg(int signal)
{
    i=1;
}

void new_enreg(int signal)
{
    i=2;
}

int main(void)
{
    struct sigaction s;
    int compteur=0;

    s.sa_handler=enreg;
    s.sa_flags=0;
    sigemptyset(&s.sa_mask);
    sigaddset(&s.sa_mask, SIGTERM);

    if (sigaction(SIGINT, &s, NULL) == -1)
    {
        perror("sigaction");
        return -1;
    }
    
    s.sa_handler=new_enreg;
    sigemptyset(&s.sa_mask);
    sigaddset(&s.sa_mask, SIGINT);
    
    if (sigaction(SIGTERM, &s, NULL) == -1)
    {
        perror("sigaction");
        return -1;
    }
    
    file_in = open("fichier.tmp", O_RDONLY | O_CREAT | O_WRONLY, 0666);
    if (file_in == -1)
    {
        perror("open");
        return -1;
    }

    while(sign == 0)
    {
        compteur++;
    }

    
    return 0;
}
