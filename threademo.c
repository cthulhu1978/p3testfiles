#include <stdio.h>
#include <pthread.h>

void* sub(void *arg);

int shared_var;
pthread_mutex_t m;

int main(int argc,char *argv[])
{
    int i, rc;
    pthread_t thrdid;

    pthread_mutex_init(&m, NULL);

    shared_var = 0;
    rc = pthread_create(&thrdid,NULL,sub,(void *)NULL);

    sub(NULL);

    pthread_join(thrdid,NULL);

    printf("shared_var=%d\n",shared_var);

    return 0;
}

void* sub(void *arg)
{
    int i;

    for (i=0; i < 1000000; i++)
    {
        pthread_mutex_lock(&m);
	shared_var += 2;
        pthread_mutex_unlock(&m);
        // sched_yield();
    }
}
