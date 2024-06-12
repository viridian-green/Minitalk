#include "minitalk.h"

static int g_signal_received = 0;

void ft_resp_handler(int signum)
{
	g_signal_received = 1;
	(void)signum;
}

void ft_send_bit(int pid, int bit)
{
	int signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error. Failed to send signal", 2);
		exit(1);
	}
	while (g_signal_received == 0)
		usleep(16);
	g_signal_received = 0;
}

void ft_send_char(int pid, unsigned char c)
{
	int bit;

	bit = 7;
	while (bit >= 0)
	{
		ft_send_bit(pid, (c >> bit) & 1);
		usleep(400);
		bit--;
	}
}

void ft_send_string(int pid, const char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0');
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
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR2, ft_resp_handler);
	ft_send_string(pid, argv[2]);
	return 0;
}