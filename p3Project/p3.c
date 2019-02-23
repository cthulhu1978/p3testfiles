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
    // required
    alarm(90);
    // how many args are presented:
    int num_args = (argc-1) / 2;
    int low_values[num_args];
    int high_values[num_args];
    for (int i = 0; i < num_args; i++) {
      if(i % 2 == 0){
        low_values[i] = atoi(argv[i + 1]);
        printf("low values arguments -> %d, val in arg %d, at pos %d\n",low_values[i], atoi(argv[i+1]), i );
      }
    }
    for (int j = 0; j < num_args; j++) {
      if(j % 2 == 1) {
        high_values[j] = atoi(argv[j + 1]);
        printf("high values arguments -> %d, val in arg %d, at pos %d\n",high_values[j], atoi(argv[j+1]), j );
      }
    }
printf("\n\n" );
    for (size_t i = 0; i < num_args; i++) {
      printf("arg at low: %d at pos %d\n",low_values[i], i );
      printf("arg at high: %d at pos %d\n",high_values[i], i );
    }
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
