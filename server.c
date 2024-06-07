#include <signal.h>
#include <sys/types.h>
#include "ft_printf/include/ft_printf.h"

//A global variable is a variable declared outside of any function and can be
//accessed and modified by any part of the program.
static int flag_signal_received = 0;
#define END_TRANSMISSION '\0'

void	decrypt_signal(int signal)
{
	static int				index;
	static unsigned char	current_char;

	current_char |= (signal == SIGUSR1); //either true (1) or false (0)
	//then added to the current char variable
	index++;
	if (index == 8)
	{
	if (current_char == END_TRANSMISSION)
		ft_printf("\n");
	else
	{
		ft_printf("%c", current_char);
		index = 0;
		current_char = 0;
		flag_signal_received = 1;
		kill(getpid(), SIGUSR1);
	}
	}
	else
		current_char <<= 1;
}
//we use static variables because we want to keep the information even after
//the function is done executing.

int	main()
{
	pid_t	pid;

	pid = getpid();
	ft_printf("The PID is number is %d", pid);
	signal(SIGUSR1, decrypt_signal);
	signal(SIGUSR2, decrypt_signal);
	while (1)
	{
		if (!flag_signal_received)
			pause();
		flag_signal_received = 0;
	}
	return (0);
}
