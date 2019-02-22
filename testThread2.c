#include <pthread.h>
#include <stdio.h>

#define NUM_LOOPS 5000000
long long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void * counting_thread(void * arg){
  int offset = *(int *)arg;
  //printf("offset: %d\n",offset );
  for (size_t i = 0; i < NUM_LOOPS; i++) {
    pthread_mutex_lock(&mutex);
    sum += offset;
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
// spawn threads
  pthread_t id;
  int offset = 1;
  pthread_create(&id, NULL, counting_thread, &offset);

  pthread_t id1;
  int offset1 = -1;
  pthread_create(&id1, NULL, counting_thread, &offset1);

// join threads
  pthread_join(id, NULL);
  pthread_join(id1, NULL);


  printf("sum is %lld\n",sum );


  return 0;
}
