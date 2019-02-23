#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct prime_runner_struct{
  int low;
  int high;
  int num_primes;
};

int low_values[8];
int high_values[8];
int thread_count = 0;

void * checkPrimes(void * arg);

int main(int argc,char *argv[])
{
    // required
    alarm(90);
    // how many args are presented:
    int num_args = (argc-1);
    printf("num args %d\n\n", num_args);
    // array for high and low vals.
    int low_count = 0; int high_count = 0;
    // put values in a high and low array:
    for (int i = 0; i < num_args; i++) {
      if(i % 2 == 0){
        low_values[low_count] = atoi(argv[i + 1]);
        low_count++;
      } else if( i % 2 == 1){
        high_values[high_count] = atoi(argv[i+1]);
        high_count++;
      }
    }
    // create enough structs for the threads//
    struct prime_runner_struct args[num_args];
    // create needed threads
    pthread_t thrdid[num_args];

    int rc, ids[8];



    //printf("I am unix process %d\n",getpid());
    for (int i = 0; i < num_args/2; i++)
    {
        rc = pthread_create(&thrdid[i],NULL,checkPrimes,(void *)&args[i]);
    }

    for (int i=0; i < num_args/2; i++)
    {
        pthread_join(thrdid[i],NULL);
    }


    return 0;
}
void * checkPrimes(void * arg)
{
    struct prime_runner_struct * arg_struct = (struct prime_runner_struct *)arg;
    int val, i, n, r;
    arg_struct->low = low_values[thread_count];
    printf("low low low %d\n", arg_struct->low );
    arg_struct->high = high_values[thread_count];
    printf("high high high  %d\n", arg_struct->high );

    pthread_mutex_lock(&mutex);
    thread_count++;
    pthread_mutex_unlock(&mutex);
    i = arg_struct->low;
    val = arg_struct->high;

    for (r=sqrt((double) val);  (val % i) != 0  &&  i < r;  i++){
    if ( (val % i) != 0)
       printf("%d is prime\n",val);
    else
       printf("%d is not prime\n",val);
     }
    pthread_exit(0);
}
