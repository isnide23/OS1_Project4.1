#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argv[1] != NULL) {
		int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		int pipe_array[2];

		pipe(pipe_array);

		if (fork() == 0) //child
		{
			dup2(pipe_array[1], 1);
			close(pipe_array[0]);
			char * const *args = argv + 2;
			execvp(argv[2], args);
		}
		else //parent
		{
			close(pipe_array[1]);
			char buf[2048];
        	int i;
			
			while ((i = read(pipe_array[0], buf, sizeof buf))> 0) 
			{
			write(fd, buf, i); 
			}
			close(pipe_array[0]); 
			close(fd); 			
		}
	}

	else {
		printf("Enter in at least two commands\n");
	}
}