#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid= fork();
	if(pid<0)//tratez eroarea
		return -1;
	else if(pid>0)//instructiuni pentru parinte
	{
	    //afsez pid-ul propriu si pid-ul copilului ca in cerinta
	    printf("My PID=%d, Child PID=%d\n", getppid(), getpid());
	    //il pun pe parinte sa astepte
		pid_t pid = wait(NULL);
		printf("Child %d finished\n", getpid());
	}
	else//instructiuni pentru copil
	{
	    //argv respecta conventia obisnuita din C:
	    //pe prima pozitie se afla calea absoluta catre program
	    //apoi urmeaza argumentele
	    //lista se incheie cu null
		char *argv[] ={"ls", NULL};
		//execve suprascrie complet procesul curent, de aceea este bine ca acesta sa fie apelat dintr-un proces copil
		execve("/bin/ls", argv, NULL);
		//nu e nevoie sa punem vreun else aici pentru ca execve nu revine in program decat daca a intervenit vreo eroare
		perror(NULL);
	}
	return 0;
}
