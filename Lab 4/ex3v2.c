#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
 
void collatz(int x)
{
	printf("%d ", x);
	if(x>1)
		if(x%2==0)
		{
			collatz(x/2);
		}
		else
		{
			collatz(3*x+1);
		}
}
 
 
 
int main(int argc, char *argv[])
{
	//Aceasta este varianta in care am un singur proces parinte, cu n copii pe care ii asteapta sa termine de procesat.
	pid_t child[argc+1];
	printf("Starting parent %d\n", getpid());
	for(int i=1; i<argc; i++)
	{
		child[i]=fork();
		if(child[i]==0)
		{
			printf("Starting child process PID=%d from parent PID=%d\n", getpid(), getppid());
			int p;
			sscanf(argv[i], "%d", &p);
			printf("%d: ", p);
			collatz(p);
			printf("\n");
			exit(0);
		}
		if(child[i]<0)
		{
			return -1;	
		}
	}
	for(int i=1; i<argc; i++)
	{
		wait(NULL);
		printf("Child PID=%d from parent PID=%d is done\n", getpid(), getppid());
	}	
 
 
	return 0;
}