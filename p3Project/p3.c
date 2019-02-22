#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>


int checkPrimes(int argc, char **argv);
void* sub(void *arg);

int shared_var;
pthread_mutex_t m;

int main(int argc,char *argv[])
{
    alarm(90);
    int i, rc, ids[8];
    pthread_t thrdid[8];

    pthread_mutex_init(&m, NULL);

    shared_var = 0;

    printf("I am unix process %d\n",getpid());
    for (i=0; i < 3; i++)
    {
        ids[i] = i;
        rc = pthread_create(&thrdid[i],NULL,sub,(void *)&ids[i]);
    }

    for (i=0; i < 3; i++)
    {
        pthread_join(thrdid[i],NULL);
    }

    printf("shared_var=%d\n",shared_var);

    return 0;
}
int checkPrimes(int argc, char **argv)
{
    int val, i, n, r;

    val = atoi(argv[1]);

    for (i=2, r=sqrt((double) val);  (val % i) != 0  &&  i < r;  i++)
        ;
    if ( (val % i) != 0)
       printf("%d is prime\n",val);
    else
       printf("%d is not prime\n",val);

    return 0;
}

void* sub(void *arg)
{
    int i;

    i = *( (int *)arg );
    printf("I am thread %d in unix process %d\n",i, getpid());

    for (i=0; i < 1000000; i++)
    {
        pthread_mutex_lock(&m);
	shared_var += 2;
        pthread_mutex_unlock(&m);
        // sched_yield();
    }
}
