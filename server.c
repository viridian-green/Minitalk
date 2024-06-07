#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "ft_printf/include/ft_printf.h"

//A global variable is a variable declared outside of any function and can be
//accessed and modified by any part of the program.
static int flag_signal_received = 0;
#define END_TRANSMISSION '\0'

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int				index;
	static unsigned char	current_char;
	static pid_t client_pid = 0;
	(void)context;

	if (info != NULL) {
        if (client_pid == 0) {
            client_pid = info->si_pid; // Set client_pid if not already set
        } else if (client_pid != info->si_pid) {
            // If a different client PID is detected, reset for new message
            index = 0;
            current_char = 0;
            client_pid = info->si_pid; // Update to the new client PID
        }
    }

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
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_printf("Error. Server failed to send the ack signal to client.");
		return ;
	}
	}
	else
		current_char <<= 1;
}

// static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
// {
// 	(void)info;
// 	(void)ucontext;
// 	if (sig == SIGUSR1)
// 	{
// 		if (ft_send(NULL, -1) == -1)
// 		{
// 			ft_printf_fd(2, "Error kill\n");
// 			exit(1);
// 		}
// 	}
// }
//we use static variables because we want to keep the information even after
//the function is done executing.

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "ft_printf/include/ft_printf.h"

int	main()
{
	struct sigaction	s;
	s.sa_flags = SA_SIGINFO;
	s.sa_sigaction = signal_handler;
	sigemptyset(&s.sa_mask);
	ft_printf("The PID is number is %d", getpid());
	if (sigaction(SIGUSR1, &s, NULL) == -1)
	{
		ft_printf("Failed to register SIGUSR1 signal handler\n");
		exit(0);
	}
	else if (sigaction(SIGUSR2, &s, NULL) == -1)
	{
		ft_printf("Failed to register SIGUSR2 signal handler\n");
		exit(0);
	}
	// sigaction(SIGUSR1, &s, NULL);
	// sigaction(SIGUSR2, &s, NULL);
	while (1)
	{
		if (!flag_signal_received)
			pause();
		flag_signal_received = 0;
	}
	return (0);
}
