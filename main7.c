#include <pthread.h>  // Include suitable header file
#include <stdio.h>
#include <stdlib.h>   // For dynamic memory allocation

#define NUM_THREADS 3

int *evenarr, *oddarr;
int je = 0, jo = 0, evensum = 0, sumn = 0, oddsum = 0;

void *Even(void *threadid)
{
    int i, n;
    n = *((int *)threadid);
    evenarr = (int *)malloc((n / 2) * sizeof(int));  // Allocate memory dynamically based on N

    for(i = 1; i <= n; i++)
    {
        if(i % 2 == 0)
        {
            evenarr[je] = i;
            evensum += i;
            je++;
        }
    }
    pthread_exit(NULL);
}

void *Odd(void *threadid)
{
    int i, n;
    n = *((int *)threadid);
    oddarr = (int *)malloc((n / 2) * sizeof(int));  // Allocate memory dynamically based on N

    for(i = 1; i <= n; i++)
    {
        if(i % 2 != 0)
        {
            oddarr[jo] = i;
            oddsum += i;
            jo++;
        }
    }
    pthread_exit(NULL);
}

void *SumN(void *threadid)
{
    int i, n;
    n = *((int *)threadid);

    for(i = 1; i <= n; i++)
    {
        sumn += i;
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int t;

    printf("Enter a number: ");
    scanf("%d", &t);
   
    pthread_create(&threads[0], NULL, Even, (void *)&t);
    pthread_create(&threads[1], NULL, Odd, (void *)&t);  
    pthread_create(&threads[2], NULL, SumN, (void *)&t);  
   
    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
   
    printf("The sum of first N natural numbers is %d\n", sumn);
    printf("The sum of first N even numbers is %d\n", evensum);
    printf("The sum of first N odd numbers is %d\n", oddsum);
   
    printf("The first N Even numbers are: ");
    for(int i = 0; i < je; i++)
    {
        printf("%d ", evenarr[i]);
    }
   
    printf("\nThe first N Odd numbers are: ");
    for(int i = 0; i < jo; i++)  
    {
        printf("%d ", oddarr[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(evenarr);
    free(oddarr);

    return 0;
}
