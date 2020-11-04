#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid= fork();
	if(pid<0)
		return -1;
	else if(pid>0)
	{
	    printf("My PID=%d, Child PID=%d\n", getppid(), getpid());
		pid_t pid = wait(NULL);
		printf("child %d finished\n", getpid());
	}
	else
	{
		char *argv[] ={"ls", NULL};
		execve("/bin/ls", argv, NULL);
		perror(NULL);
	}
	return 0;
}
