/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:36:48 by ademarti          #+#    #+#             */
/*   Updated: 2024/06/12 15:14:28 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char character = 0;
	static int	bit_count = 0;
	static pid_t	client_pid = 0;

 	(void)context;
 	if (client_pid != info->si_pid)
 	{
  		bit_count = 0;
  		character = 0;
 	}
 	client_pid = info->si_pid;
 	character = character << 1;
 	if (signum == SIGUSR1)
  		character = character | 1;
 	bit_count++;
 	if (bit_count == 8)
 	{
  		write(1, &character, 1);
  		bit_count = 0;
  		character = 0;
	 }
 	kill(client_pid, SIGUSR2);
}

int	main()
{
	struct sigaction sa;

 	ft_printf("The server PID is %d\n", getpid());
 	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
 	sigaction(SIGUSR1, &sa, NULL);
 	sigaction(SIGUSR2, &sa, NULL);

	while (1)
			pause();
	return (0);
}
