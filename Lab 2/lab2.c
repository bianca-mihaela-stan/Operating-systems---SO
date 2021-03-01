#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#define BUFFER_SIZE 4000

int min(int x, int y)
{
    if (x<=y) return x;
    return y;
}

int mycp(char fisier1[], char fisier2[])
{
    int fd1, fd2;
    ssize_t nr1, nr2;
    char buffer[BUFFER_SIZE+5];
    fd1=open(fisier1, O_RDONLY);
    fd2=open(fisier2, O_WRONLY);


    memset(buffer, 0, BUFFER_SIZE+5);
    if(fd1<0)
    {
        perror("Eroare la deschiderea fisierului de citire!");
        return errno;
    }
    else if(fd2<0)
    {
        close(fd1);
        perror("Eroare la deschiderea fisierului de scriere!");
        return errno;
    }
    else
    {
        while(nr1=read(fd1, buffer, BUFFER_SIZE)>0)
        {
            if(nr1<0)
            {
                close(fd1);
                close(fd2);
                return 0;
            }
            printf("\n%s\n", buffer);
            nr2=write(fd2, buffer, strlen(buffer));
            memset(buffer, 0, BUFFER_SIZE+5);
            if(nr2<0)
            {
                perror("Eroare la scrierea in fisier");
                return errno;
            }
        }
        close(fd1);
        close(fd2);
        return 0;
    }

}
int main()
{
    char m[50]="Hello World!\n";
    write(1, m, sizeof(m));
    return mycp("test1.txt", "test2.txt");
}
