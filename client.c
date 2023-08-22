#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// int main(int ac, char **av)
// {

//     int i ;
//     (void)ac;
//     i =  0;
    
//     while(i < 8)
//     {
//         if( i% 2 == 0)
//         kill((pid_t)atoi(av[1]), SIGUSR1);
//         else
//         kill((pid_t)atoi(av[1]), SIGUSR2);
//         usleep(100);
//         i++;
//     }
//     return 0;
// }

void send_signal(unsigned char c,pid_t pid)
{
	int digit;

	digit = 7;

	while (digit >= 0)
	{
		if ((c >> digit) & 0x01)
			kill(pid,SIGUSR1);
		else
		kill(pid,SIGUSR2);
		digit--;
		usleep(150);
	}

	digit = 7;
}

void send_char(char *str,pid_t pid)
{
	unsigned char c;
	while (*str != '\0')
	{
		c = (unsigned char)(*str);
		send_signal(c, pid);
		str++;
	}
}

int	main(int ac, char **av)
{
	pid_t pid;

	pid = (pid_t)atoi(av[1]);
	if(ac != 3)
	{
		write(1,"error. please input : ./client PID XXXX\n",40);
		return(0);
	}
	send_char(av[2],pid);
	return(0);
}
