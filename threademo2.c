#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* sub(void *arg);

int shared_var;
pthread_mutex_t m;

int main(int argc,char *argv[])
{
  // array of ints?
    int i, rc, ids[8];
    pthread_t thrdid[8];

    pthread_mutex_init(&m, NULL);

    shared_var = 0;
// print unix proces id, create extra threads, lightweight threads of execution in on heavyW process
// So One UNIX ID
    printf("I am unix process %d\n",getpid());
    for (i=0; i < 3; i++)
    {
        ids[i] = i;
        // savind a vector of thread ID'S
        rc = pthread_create(&thrdid[i],NULL,sub,(void *)&ids[i]);
    }

    for (i=0; i < 3; i++)
    {
        pthread_join(thrdid[i],NULL);
    }

    printf("shared_var=%d\n",shared_var);

    return 0;
}
// have to pass a pointer to void. But in pthread create case as void name(/* arguments */) {
  /* code
receive a pointer to void but recast to a pointer to an integer and dereference
  */
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
