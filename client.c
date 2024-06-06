#include <signal.h>
#include <sys/types.h>
#include "libft/libft.h"
#include "ft_printf/include/ft_printf.h"

void	send_signal(int pid, unsigned char character)
{
	int	i;
	unsigned char temp_char;

	i = 8;
	temp_char = character;
	while (i--)
	{
	temp_char = character >> i;
		if (temp_char % 2 == 0) //if bit is 0
			kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1); //if bit is 1
	usleep(100); //Pause for 50 microseconds to ensure that the signals
	//are sent with a slight delay to prevent signal flooding.
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int	i;

	pid = ft_atoi(argv[1]);
	i = 0;
	if (argc != 3)
	{
		ft_printf("Invalid input. Please enter two parameters: \
		the PID number and a message to be sent.");
		exit(0);
	}
	else
	{
	while (argv[2][i])
	{
		send_signal(pid, (unsigned char)argv[2][i]);
		i++;
	}
	}
	return 0;
}