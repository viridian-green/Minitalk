/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:36:48 by ademarti          #+#    #+#             */
/*   Updated: 2024/06/12 18:42:15 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit_count;
	static pid_t			client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		bit_count = 0;
		c = 0;
	}
	client_pid = info->si_pid;
	c = c << 1;
	if (signum == SIGUSR1)
		c = c | 1;
	else if (signum == SIGUSR2)
		c = c | 0;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR2);
}


int	main()
{
	struct sigaction	sa;

	ft_printf("The server PID is %d\n", getpid());
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
 	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error. Failed to set up signal handler for SIGUSR1.", 2);
		exit(1);
	}
 	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error. Failed to set up signal handler for SIGUSR1.", 2);
		exit(1);
	}
	while (1)
			pause();
	return (0);
}
