#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void send_signal(int pid, unsigned char character)
{
 	int    i;
 	unsigned char temp_char;

 	i = 8;
 	temp_char = character;
	printf("received bit");
 	while (i--)
 	{
  	temp_char = character >> i;
  	if (temp_char % 2 == 0) //if bit is 0
   		kill(pid, SIGUSR2);
  	else
   		kill(pid, SIGUSR1); //if bit is 1
  	usleep(50); //Pause for 50 microseconds to ensure that the signals
	//are sent with a slight delay to prevent signal flooding.
	}
}

int main(int argc, char **argv)
{
	pid_t pid;
	pid = atoi(argv[1]);
	int i = 0;
	while (argv[2][i])
	{
		send_signal(pid, (unsigned char)argv[2][i]);
		i++;
	}
	(void)argc;
  return 0;
}