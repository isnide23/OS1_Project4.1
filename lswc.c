#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[])
{

	// pipe_array[0] is for reading 
	// pipe_array[1] is for writing 
	int pipe_array[2];

	pipe(pipe_array);

	if (fork() == 0)
	{
		dup2(pipe_array[0], 0);
		close(pipe_array[1]);
		execlp("wc", "wc", "-l",  NULL);
	}
	else
	{
		dup2(pipe_array[1], 1);
		close(pipe_array[0]);
		execlp("ls","ls", "-la", argv[1], NULL);
	}
}