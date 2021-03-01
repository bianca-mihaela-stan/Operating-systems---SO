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
	if(pid<0)//tratez eroarea
		return -1;
	else if(pid==0)//instructiuni pentru procesul copil
	{
		int x;
		scanf("%d", &x);//citesc argumentul
		printf("%d: ", x);
		collatz(x);//apelez functia corespunzatoare
		printf("\n");
	}
	else//instructiuni pentru procesul parinte
	{
		pid_t cpid=wait(NULL);
		printf("Child %d finished\n", getppid());
	}
	return 0;
}
