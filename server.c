#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//A global variable is a variable declared outside of any function and can be
//accessed and modified by any part of the program.

void client(pid_t pid)
{

		printf("The PID is %d\n", pid);
			exit(0);

}
/*
void signal_handler(int signum)
{
  //printf("Received SIGINT!\n", signum);
  exit(0);
}
*/

void send_signal(int pid, unsigned char character)
{
 	int    i;
 	unsigned char temp_char;

 	i = 8;
 	temp_char = character;
 	while (i--)
 {
  	temp_char = character >> i;
  	if (temp_char % 2 == 0)
   		kill(pid, SIGUSR2);
  	else
   		kill(pid, SIGUSR1);
  	usleep(42);
 }
}

int main(int argc, char **argv)
{

	pid_t pid;
	pid = getpid();
	//signal(SIGINT, signal_handler);
	/*
	int result;
	result = kill(pid, SIGTERM);
	if (result == 0)
		printf("Signal sucessfully sent.");
	else
		printf("failed");
  	client(pid);
	*/
	(void)argv;
	(void)argc;
	printf("%d", pid);

	return (0);
}