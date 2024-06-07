#include <signal.h>
#include <sys/types.h>
#include "libft/libft.h"
#include "ft_printf/include/ft_printf.h"

// "Here, it is: for many, the first day of going back into the routine of work, school, volunteer roles and so many more activities, with the hectic hustle of the holidays behind us — looking down 364 days of new and exciting ways of doing things, of doing something you’ve want done for decades the same way but you think — given your extensive experience — you can go about it differently, bringing more productivity, more satisfaction, being an example to others around you, and — you know what they say about flattery — they start do the same thing because … you showed the way."

static int ack_received = 0;

void ack_handler(int signal)
{
    (void)signal;  // Explicitly mark the parameter as unused
    ack_received = 1;
}

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
	while (!ack_received)
	{
		pause();
	}
	ack_received = 0;
	usleep(200);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ack_handler);
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
	// send_signal(pid, '\0');
	}
	return 0;
}