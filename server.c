#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

//A global variable is a variable declared outside of any function and can be
//accessed and modified by any part of the program.
int flag_signal_received = 0;
#define END_TRANSMISSION '\0'

/*
void signal_handler(int signum)
{
   if (signum == SIGUSR1)
        printf("Received SIGUSR1 (bit 1)\n");
    else if (signum == SIGUSR2)
        printf("Received SIGUSR2 (bit 0)\n");
	decrypt_signal(signum);
	exit(0);
}
*/

void decrypt_signal(int signal)
{
 	static int    index;
 	static unsigned char current_char;

	current_char |= (signal == SIGUSR1); //either true (1) or false (0)
	//then added to the current char variable
	index++;
 	if (index == 8)
	{
 	if (current_char == END_TRANSMISSION)
		printf("\n");
	else
	{
   		printf("%c", current_char);
		index = 0;
  		current_char = 0;
		flag_signal_received = 1;
	}
	}
	else
  		current_char <<= 1;

}
//we use static variables because we want to keep the information even after
//the function is done executing.

int main()
{

	pid_t pid;
	pid = getpid();
	printf("The PID is %d\n", pid);
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

    	//printf("Exiting pause.\n");
	/*
	int result;
	result = kill(pid, SIGTERM);
	if (result == 0)
		printf("Signal sucessfully sent.");
	else
		printf("failed");
	*/