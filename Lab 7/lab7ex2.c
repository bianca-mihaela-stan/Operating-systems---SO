#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#define NTHRS 5
 
sem_t semafor;
pthread_mutex_t mtx;
int nr_fire_la_bariera=0;
 
void barrier_point()
{
    //nr_fire_la_bariera este o variabila globala pe care toate thread-urile vor sa o modifice
    //ca valoarea ei finala sa fie cea corecta, o incadrez intr-un mutex
    pthread_mutex_lock(&mtx);
    nr_fire_la_bariera++;
    pthread_mutex_unlock(&mtx);
 
    if(nr_fire_la_bariera<NTHRS)//daca ince nu avem 5 fire la bariera
    {
        if(sem_wait(&semafor))//le punem sa astepte
        {
            perror("eroare la semafor");
            return errno;
        }
    }
    else for(int j=0; j<NTHRS; j++)//daca toate firele sunt la bariera le dau drumul la toate
        sem_post(&semafor);
 
 
}
 
 
void * tfun(void *v)
{
    int tid = *((int*) v);
    printf("%d reached the barrier\n", tid);
    barrier_point();
    printf("%d passed the barrier\n", tid);
 
    return NULL;
}
 
 
int main()
{
    pthread_t thr[NTHRS+1];//creez vectorul de thread-uri
 
    if(sem_init(&semafor, 0, nr_fire_la_bariera)){//creez semaforul
        perror("eroare la crearea semaforului\n");
        return errno;
    }
 
    if(pthread_mutex_init(&mtx, NULL))//creez mutex-ul
    {
        perror("eroare la crearea mutexului");
        return errno;
    }
 
    int v[NTHRS];//vreau ca fiecaru thread sa ii dau un "numar" ca sa imi fie mai usor sa le disting
    //daca as pune void *k=i, cum i se modifica, toate thread-urile s-ar numi 5
    //asa ca fiecare k arata catre o zona diferita de memorie din vectorul v
    for(int i=0; i<NTHRS; i++)
    {
        v[i]=i;
        void* k = &v[i];
        if(pthread_create(&thr[i], NULL, tfun, k))//creez thread-urile
        {
            perror("eroare la crearea firului de executie\n");
            return errno;
        }
    }
 
    for(int i=0; i<NTHRS; i++)//fac join la thread-uri
    {
        if(pthread_join(thr[i], NULL))
        {
            perror("eroare la join-ul firelor de executie\n");
            return errno;
        }
    }
 
    //distrug semaforul si mutex-ul
    sem_destroy(&semafor);
    pthread_mutex_destroy(&mtx);
}