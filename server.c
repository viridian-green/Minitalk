#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

//A global variable is a variable declared outside of any function and can be
//accessed and modified by any part of the program.

/*
void signal_handler(int signum)
{
  //printf("Received SIGINT!\n", signum);
  exit(0);
}
*/

int main(int argc, char **argv)
{

	pid_t pid;
	pid = getpid();
	printf("The PID is %d\n", pid);
	//signal(SIGINT, signal_handler);
	/*
	int result;
	result = kill(pid, SIGTERM);
	if (result == 0)
		printf("Signal sucessfully sent.");
	else
		printf("failed");
	*/

	(void)argv;
	(void)argc;
	return (0);
}