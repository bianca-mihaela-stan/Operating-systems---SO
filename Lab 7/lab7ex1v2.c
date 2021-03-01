#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
 
#define MAX_RESOURCES 5
#define NUMAR_TOTAL_THREADS 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;
 
int decrease_count(int count)
{
    //am nevoie de un mutex pentru ca vreau sa un singur thread sa poate modifica valoarea lui available_resources la un moment dat
    pthread_mutex_lock(&mtx);
    if(available_resources<count)//daca nu se gasesc destul resurse nu inseamna ca thread-ul cere prea multe, ci ca in momentul asta nu sunt disponibile
    {
        pthread_mutex_unlock(&mtx);
        printf("Got %d resources, only %d resources available\n", count, available_resources);//afisez faptul ca nu se gasesc
 
 
        //ACEASTA ESTE MODIFICAREA FATA DE VARIANTA INITIALA
        return -1; //acest thread nu va fi "servit" niciodata
    }
    else//daca sunt destul resurse doar fac update la available_resources
    {
        available_resources = available_resources - count;
        printf("Got %d resources, remaining %d resources\n", count, available_resources);
    }
 
    pthread_mutex_unlock(&mtx);//deschid mutex-ul
 
    return 0;
 
}
 
 
int increase_count(int count)
{
    //imi trebuie din nou un mutex pentru ca fac update la available_resources
    pthread_mutex_lock(&mtx);
    available_resources+=count;
    printf("Released %d resources, remaining %d resources\n", count, available_resources);
    pthread_mutex_unlock(&mtx);
 
    return 0;
}
 
 
void * fct(void * arg)
{
    //res este numarul de resurse cerute de thread-ul curent
    int res= (int) arg;
    if(decrease_count(res)==0)//doar daca am reusit sa fac decrease la count pot face increase
    {
        //am pus fiecare thread sa astepte putin, pentru ca altfel nu se suprapuneau deloc thread-urile si nu se vedea cum se executa programul
        //daca nu puneam sleep aveam "Got x, Released x, Got y, Released y"
        sleep(1);
        increase_count(res);
    }
 
    return NULL;
}
 
 
 
int main()
{
    if(pthread_mutex_init(&mtx, NULL))//creez mutex-ul
    {
        perror("Eraore la crearea mutexului. \n");
        return errno;
    }
 
    pthread_t thr[NUMAR_TOTAL_THREADS];//fac thread-urile
    srand(time(0));
    for(int i=0; i<NUMAR_TOTAL_THREADS; i++)
    {      
        int res=rand()%(MAX_RESOURCES+1);
        if(pthread_create(&thr[i], NULL, fct, res))//creez thread-ul
        {
            perror("Nu s-a putut crea thread-ul.\n");
            return errno;
        }
    }
 
    for(int i=0; i<NUMAR_TOTAL_THREADS; i++)//fac join la thread-uri
    {      
        pthread_join(thr[i], NULL);
    }
 
    pthread_mutex_destroy(&mtx);//distrug mutex-ul
    return 0;
}