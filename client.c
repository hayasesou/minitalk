#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int signal_success = 1;

void handler(int signum, siginfo_t *server, void *con)
{
	(void)server;
	(void)con;

	if(signum == SIGUSR1 )
	{
		signal_success = 1;
		write(1,"0",1);
	}
}


static void	send_signal(unsigned char c, pid_t pid)
{
	int	digit;

	digit = 7;
	while (digit >= 0)
	{
		usleep(150);
		if ((c >> digit) & 0x01)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				write (1, "error. SIGUSR1", 14);
				exit(0);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write (1, "error. SIGUSR2", 14);
				exit(0);
			}
		}
		signal_success = 0;
		digit--;
	}
	digit = 7;
	write(1,"1",1);
}

static void	send_char(char *str, pid_t pid)
{
	unsigned char	c;

	while (*str != '\0')
	{
		c = (unsigned char)(*str);
		send_signal(c, pid);
		str++;
	}
	exit(1);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	struct  sigaction client_sa;

	pid = (pid_t)ft_atoi(av[1]);
	if (pid < 100 || pid > 99998)
	{
		write (1, "error. invalid PID\n", 19);
		return (-1);
	}
	if (ac != 3)
	{
		write (1, "error. please input : ./client PID XXXX\n", 40);
		return (-1);
	}
	ft_memset(&client_sa, 0, sizeof(struct sigaction));
	sigemptyset(&client_sa.sa_mask);
	client_sa.sa_sigaction = handler;
	client_sa.sa_flags = SA_SIGINFO; 
	sigaction (SIGUSR1, &client_sa, NULL);
	sigaction (SIGUSR2, &client_sa, NULL);
	send_char(av[2],pid);
	while(1)
	{
	pause();
	}
	return (0);
}
