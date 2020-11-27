#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
 
void* reverse (void* str)
{
    char *str2=(char *)str;
    char *res=(char *)malloc(strlen(str2));
    for(int i=0; i<strlen(str2); i++)
    {
        res[strlen(str2)-1-i]=str2[i];
    }
    return res;
}
 
int main(int argc, char *argv[])
{
    if(argc>1)
    {
        void *result;
        pthread_t thread;
        if(pthread_create(&thread, NULL, reverse, argv[1]))
        {
            perror("The thread could not be created.\n");
            return errno;
        }
 
        if(pthread_join(thread, &result))
        {
            perror("Error in joining the thread.\n");
            return errno;
        }
 
        char* result2=(char *)result;
        printf("%s\n", result2);
    }
    else
    {
        perror("You need to provide an argument.\n");
        return errno;
    }
 
    return 0;
}