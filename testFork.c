#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int i = 0;
void doWork(char * name){
  const int numTimes = 5;
  for (; i < numTimes; i++) {
    sleep(rand() % 4);
    printf("done pass %d for %s\n",i, name );
  }
  printf("exiting doWork\n" );

}


int main(int argc, char const *argv[]) {

  printf("I am : %d\n",(int)getpid() );

  pid_t pid = fork();
  srand((int)pid);
  printf("fork returned: %d\n",pid );

  if(pid == 0){
    printf("C-> %d is the child\n", (int)getpid() );
    // call function from child process //
    doWork("Child");
    exit(42);
  }


    printf("P-> %d is the PARENT waiting for child to end\n", (int)getpid() );
    doWork("Parent");
    int status = 0;
    pid_t childPid = wait(&status);
    printf("return from wait: %d and finished with status %d\n",(int)childPid, status );
    int childReturnval = WEXITSTATUS(status);
    printf("child return val %d\n",childReturnval ); 
    sleep(3);
    printf("Done waiting\n" );
  return 0;
}
