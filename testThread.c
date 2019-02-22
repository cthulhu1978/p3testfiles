#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
// thread function to generate some  0 to N

// global
long long sum = 0;

void * sum_runner(void * arg)
{
    int * limit_ptr = (int *)arg;
    int limit = *limit_ptr;
    for(int i = 0; i < limit; i++){
      sum += i;
      printf("sum is now: %lld\n",sum );
    }
    pthread_exit(0);
}
/*
pthread_create pass in pointer to a function
*/


int main(int argc, char **argv) {
  pthread_t thread1;
  pthread_attr_t attr;

  int limit  = atoll(argv[1]);

  pthread_attr_init(&attr);
  pthread_create(&thread1, &attr, sum_runner, &limit);
  // wait until thread has done its work

  pthread_join(thread1, NULL);
  printf("sum is %lld\n",sum );

  return 0;
}
