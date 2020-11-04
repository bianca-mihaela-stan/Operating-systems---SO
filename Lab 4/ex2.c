#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
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
int main()
{
	pid_t pid= fork();
	if(pid<0)
		return -1;
	else if(pid==0)
	{
		int x;
		scanf("%d", &x);
		printf("%d: ", x);
		collatz(x);
		printf("\n");
	}
	else
	{
		pid_t cpid =wait(NULL);
		printf("Child %d finished\n", getppid());
	}
	return 0;
}
