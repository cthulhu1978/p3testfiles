#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* sub(void *arg);

int shared_var;
pthread_mutex_t m;

int main(int argc,char *argv[])
{
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
