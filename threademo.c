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
/*
fill in thread address operator, NULL is the default attribute, sub method is called
pointer to function where the thead can execute. Takes one argumen, a pointer to a void and a return
type of void. Then pointer to argument you want to pass to the thread. NULL is here because
we do not want to pass anything.
*/
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
