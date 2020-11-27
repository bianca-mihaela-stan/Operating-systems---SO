#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
 
int **A, **B;
int m1, n1, m2, n2, k;
struct element
{
    int x;
    int y;
};
 
void * multiply(void * arg)
{
    struct element *a=arg;
    int *sum=(int*)malloc(sizeof(int));
    *sum=0;
    for(int i=0; i<m1; i++)
    {
        *sum+=A[a->x][i]*B[i][a->y];
    }
    return sum;
}
 
int main(int argc, char *argv[])
{
    void *result;
    printf("Number of rows of first matrix: ");
    scanf("%d", &n1);
    printf("\nNumber of columns of first matrix: ");
    scanf("%d", &m1);
    printf("\nElements in the first matrix: ");
 
    A=(int**)malloc(sizeof(int) *n1);
    for(int i=0; i<n1; i++)
    {
        A[i]=(int*) malloc(sizeof(int)*m1);
        for(int j=0; j<m1; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
 
    printf("\n\nNumber of rows of second matrix: ");
    scanf("%d", &n2);
    printf("\nNumber of columns of second matrix: ");
    scanf("%d", &m2);
    printf("\nElements in the second matrix: ");
 
    B=(int**)malloc(sizeof(int) *n2);
    for(int i=0; i<n2; i++)
    {
        B[i]=(int*) malloc(sizeof(int)*m2);
        for(int j=0; j<m2; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }
 
 
    printf("Matrix A is: \n");
        for(int i=0; i<n1; i++)
        {
            for(int j=0; j<m1; j++)
            {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
 
 
    printf("Matrix B is: \n");
        for(int i=0; i<n2; i++)
        {
            for(int j=0; j<m2; j++)
            {
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }
 
 
 
 
    if(m1!=n2)
    {
        perror("\nThe 2 matrixes cannot be multiplied.\n");
        return errno;
    }
    else
    {
        pthread_t thread[n1*m2];
        int C[n1][m2];
 
        for(int i=0; i<n1; i++)
        {
            for(int j=0; j<m2; j++)
            {
                //imi trebuie un struct ca sa trimit 2 argumente
                struct element *x=(struct element*)malloc(sizeof(struct element));
                x->x=i;
                x->y=j;
 
                if(pthread_create(&thread[k++], NULL, multiply, x))
                {
                    perror("The thread could not be created.\n");
                    return errno;
                }
 
            }
        }
 
        k=0;
        for(int i=0; i<n1; i++)
        {
            for(int j=0; j<m2; j++)
            {
                if(pthread_join(thread[k++], &result))
                {
                    perror("The thread could not be joined.\n");
                    return errno;
                }
                C[i][j]=*((int*)result);
            }
        }
 
 
        printf("Matrix C is: \n");
        for(int i=0; i<n1; i++)
        {
            for(int j=0; j<m2; j++)
            {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
 
        for(int i=0; i<n1; i++) free(A[i]);
        for(int i=0; i<n2; i++) free(B[i]);
    }
 
 
    return 0;
}