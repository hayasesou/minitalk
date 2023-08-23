/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:50:28 by hfukushi          #+#    #+#             */
/*   Updated: 2023/08/23 13:50:31 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int			g_signal_success = 0;

void	handler(int signum, siginfo_t *server, void *con)
{
	(void)server;
	(void)con;
	if (signum == SIGUSR1)
	{
		g_signal_success = 1;
		write(1, "ACK\n", 4);
	}
}

static void	send_signal(unsigned char c, pid_t pid)
{
	int	digit;

	digit = 7;
	while (digit >= 0)
	{
		usleep(50);
		if ((c >> digit) & 0x01)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		digit--;
		while (g_signal_success == 0)
			;
		g_signal_success = 0;
	}
	digit = 7;
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
	exit(0);
}

int	main(int ac, char **av)
{
	pid_t					pid;
	struct sigaction		client_sa;

	pid = (pid_t)ft_atoi(av[1]);
	if (pid < 100 || pid > 99998)
	{
		write(1, "error. invalid PID\n", 19);
		return (-1);
	}
	if (ac != 3)
	{
		write(1, "error. please input : ./client PID XXXX\n", 40);
		return (-1);
	}
	ft_memset(&client_sa, 0, sizeof(struct sigaction));
	sigemptyset(&client_sa.sa_mask);
	client_sa.sa_sigaction = handler;
	client_sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &client_sa, NULL);
	sigaction(SIGUSR2, &client_sa, NULL);
	send_char(av[2], pid);
	while (1)
		pause();
	return (0);
}
