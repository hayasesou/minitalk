#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{

    int i ;
    (void)ac;
    i =  0;
    
    while(i < 8)
    {
        if( i% 2 == 0)
        kill((pid_t)atoi(av[1]), SIGUSR1);
        else
        kill((pid_t)atoi(av[1]), SIGUSR2);
        usleep(100);
        i++;
    }
    return 0;
}
