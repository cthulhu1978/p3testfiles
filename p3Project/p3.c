#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <string.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct prime_runner_struct{
  int low;
  int high;
  int num_primes;
};

double time1()
{
    struct timeval tv;
    gettimeofday( &tv, ( struct timezone * ) 0 );
    return ( (double) (tv.tv_sec + (tv.tv_usec / 1000000.0)) );
}
double timeStart, timeEnd;
int low_values[8];
int high_values[8];
int thread_count = 0;

void * checkPrimes(void * arg);

int main(int argc,char *argv[])
{
    // required alarm
    alarm(180);
    timeStart = time1();
    // check for args //
    if(argc < 2){exit(0);}
    if(strcmp(argv[1], "-hw") == 0) { printf("%s\n","Hello world" ); exit(0); }

    int num_args = (argc-1);
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
    struct prime_runner_struct args[num_args/2];

    // create needed threads
    pthread_t thrdid[num_args/2];
    int rc;

    //printf("I am unix process %d\n",getpid());
    for (int i = 0; i < num_args/2; i++){rc = pthread_create(&thrdid[i],NULL,checkPrimes,(void *)&args[i]);}

    for (int i=0; i < num_args/2; i++) { pthread_join(thrdid[i],NULL);}

    int total_primes = 0;
    for (size_t i = 0; i < num_args/2; i++) { total_primes += args[i].num_primes; }

    timeEnd = time1();
    double cpu_time = (double)(timeEnd - timeStart);

    printf("%.3lf     ",cpu_time );
    printf("%d",total_primes );
    for (size_t i = 0; i < num_args/2; i++) { printf(" %d", args[i].num_primes );}
    printf("\n");
    return 0;
}
void * checkPrimes(void * arg)
{
    //printf("thread num: %ld\n",pthread_self() );
    pthread_mutex_lock(&mutex);
    int high_range, low_range, n, r;

    struct prime_runner_struct * arg_struct = (struct prime_runner_struct *)arg;
    arg_struct->num_primes = 0;
    arg_struct->low = low_values[thread_count];
    arg_struct->high = high_values[thread_count];

    thread_count++;

    high_range = (int)arg_struct->high;
    low_range =  (int)arg_struct->low;

    for (int i = high_range; i >= low_range; i--) {
      bool isPrime = true;
      for (int j = 2; j <= high_range; j++) {
        if(i % j == 0 && i != j){
            isPrime = false;
            //printf("i: %d mod j: %d \n",i, j );
          }
        } // end inner for loop
        if(isPrime == true){
          //printf("prime is %d\n", i );
          arg_struct->num_primes += 1;
        }
        isPrime = true;
      } // end second for loop
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
