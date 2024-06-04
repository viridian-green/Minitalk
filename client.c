#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
void client(pid_t pid, char **argv)
{
		printf("The PID is %d\n", pid);
			exit(0);
}
*/

void send_signal(int pid, unsigned char character)
{
	printf("%d\n", pid);
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
	pid = atoi(argv[1]);
	printf("%d\n", pid);
	int i = 0;
	while (argv[2][i])
	{
		send_signal(pid, (unsigned char)argv[2][i]);
		i++;
	}
	(void)argc;
  return 0;
}