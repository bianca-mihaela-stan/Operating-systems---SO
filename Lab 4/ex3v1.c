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
 
int fork_it(int argc, int x, char *argv[])
{
	if(x==argc)//daca sunt la ultimul argument
	{
		int p;
		sscanf(argv[x], "%d", &p);
		printf("%d: ", p);
		collatz(p);
		printf("\n");//fac procesarea pe Collatz
		return 0;
	}
	else//daca nu sunt la ultimul numar
	{
		pid_t pid=fork();//mai fac un copil din copilul curent
		if(pid<0)
			return -1;//tratez erorile daca sunt
		else if(pid==0)
		{
			return fork_it(argc, x+1, argv);
		}
		else
		{
			pid_t cpid =wait(NULL);//copilul trebuie la randul sau sa astepte dupa copil
			//dupa ce se termina copilul poate sa inceapa si el sa proceseze
			printf("Child PID=%d with parent PID=%d is done\n", getppid(), getpid());
			printf("Starting child PID=%d\n", getppid());
			int p;
			sscanf(argv[x], "%d", &p);
			printf("%d: ", p);
			collatz(p);
			printf("\n");
		}
	}
}
int main(int argc, char *argv[])
{
	//Aceasta este varianta de implementare care creeaza un "lant" de procese. Se porneste de la un parinte creeaza copilul 1 si il asteapta. Copilul 1 creeaza si el copilul 2 si il asteapta. .... In final, copilul 4 va face Collatz pe 36, copilul 3 pe 25, copilul 2 pe 16, copilul 1 pe 9, iar parintele nu face nimic decat sa astepte ca copiii sa termine.
	printf("Starting parent %d\n", getpid());//se porneste procesul parinte, acesta nu va procesa niciun numar introdus
	pid_t pid= fork();//se creeaza primul copil
	if(pid<0)
		return -1;//tratez erorile
	else if(pid==0)
	{
		int x=1;
		if(argc>1)//daca mai sunt numere de procesat trimit catre functie
			return fork_it(argc, x, argv);
	}
	else
	{
		pid_t cpid =wait(NULL);//parintele trebuie sa isi astepte copilul sa termine
		printf("Child PID=%d with parent PID=%d is done\n", getppid(), getpid());
	}
	return 0;