/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:50:46 by hfukushi          #+#    #+#             */
/*   Updated: 2023/08/23 13:50:48 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <libc.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	handler(int signum, siginfo_t *client, void *con)
{
	static unsigned char	c = 0b00000000;
	static int				bit_counter = 7;

	(void)con;
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		if (signum == SIGUSR1)
			c = (1 << bit_counter) | c;
		if (bit_counter == 0)
		{
			write(1, &c, 1);
			bit_counter = 7;
			c = 0b00000000;
		}
		else
			bit_counter--;
		kill(client->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	write(1, "pid = [", 7);
	ft_putnbr_fd(pid, 1);
	write(1, "]\n", 2);
	ft_memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
