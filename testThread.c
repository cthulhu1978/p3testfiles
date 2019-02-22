#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
// thread function to generate some  0 to N
// global
long long sum = 0;
struct sum_runner_struct{
  long long limit;
  long long answer;
};

void * sum_runner(void * arg)
{
    // cast void to int pointer
    struct sum_runner_struct * arg_struct = (struct sum_runner_struct *)arg;
    printf("arg_struct->limit %lld\n",arg_struct->limit );
    for(int i = 0; i <= arg_struct->limit; i++){
      sum += i;
    }
    arg_struct->answer = sum;
    pthread_exit(0);
}
/*
pthread_create pass in pointer to a function
*/
int main(int argc, char **argv) {

  int numArgs = (argc-1);
  printf("Number of args/threads are: %d\n\n",numArgs );
  struct sum_runner_struct args[numArgs];
  pthread_t tids[numArgs];


  for (int i = 0; i < numArgs; i++) {
    args[i].limit  = atoll(argv[i + 1]);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tids[i], &attr, sum_runner, &args[i]);
    //printf("THE CURRENT PID: %d\n", getpid());
  }
  // wait until thread has done its work
  for (int j = 0; j < numArgs; j++) {
    pthread_join(tids[j], NULL);
    printf("sum is %lld for threadID: %d\n",args[j].answer, getpid() );
  }



  return 0;
}
