/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:36:41 by ademarti          #+#    #+#             */
/*   Updated: 2024/06/12 20:56:04 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_signal_received = 0;

void	catch_signal_from_server(int signal)
{
	(void)signal;
	g_signal_received = 1;
}

void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error. Failed to send signal to server.", 2);
		exit(1);
	}
	while (g_signal_received == 0)
		usleep(20);
	g_signal_received = 0;
}

void	char_to_bit(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		send_bit(pid, (c >> bit) & 1);
		usleep(400);
		bit--;
	}
}

void	handle_arguments(int argc)
{
	if (argc != 3)
	{
		ft_printf("Invalid input. Please enter two parameters: \
		the server's PID number and a message to be sent.", 2);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;

	pid = ft_atoi(argv[1]);
	str = argv[2];
	handle_arguments(argc);
	signal(SIGUSR2, catch_signal_from_server);
	while (*str)
	{
		char_to_bit(pid, (unsigned char)*str++);
	}
	char_to_bit(pid, '\0');
	return (0);
}
