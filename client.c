#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	send_signal(unsigned char c, pid_t pid)
{
	int	digit;

	digit = 7;
	while (digit >= 0)
	{
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
		digit--;
		usleep(150);
	}
	digit = 7;
}

void	send_char(char *str, pid_t pid)
{
	unsigned char	c;

	while (*str != '\0')
	{
		c = (unsigned char)(*str);
		send_signal(c, pid);
		str++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

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
	send_char(av[2],pid);
	return (0);
}
