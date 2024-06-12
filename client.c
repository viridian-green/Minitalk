/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:36:41 by ademarti          #+#    #+#             */
/*   Updated: 2024/06/12 14:56:40 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int g_signal_received = 0;

void catch_signal_from_server(int signum)
{
	(void)signum;
	g_signal_received = 1;
}

void send_bit(int pid, int bit)
{
	int signal;

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

void char_to_bit(int pid, unsigned char c)
{
	int bit;

	bit = 7;
	while (bit >= 0)
	{
		send_bit(pid, (c >> bit) & 1);
		usleep(400);
		bit--;
	}
}

void send_string(int pid, const char *str)
{
	while (*str)
		char_to_bit(pid, *str++);
	char_to_bit(pid, '\0');
}

int main(int argc, char **argv)
{
	pid_t pid;
	int i;

	pid = ft_atoi(argv[1]);
	i = 0;
	if (argc != 3)
	{
		ft_printf("Invalid input. Please enter two parameters: \
		the PID number and a message to be sent.");
		exit(0);
	}
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 2);
		exit(1);
	}
	signal(SIGUSR2, catch_signal_from_server);
	send_string(pid, argv[2]);
	return 0;
}
//Signal handler does not take '()' because it is not proceeded directly