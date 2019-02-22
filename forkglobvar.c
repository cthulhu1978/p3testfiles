#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int globvar = 909;

int main(int argc, char *argv[])
{
    int rc, status;

    rc = fork();
    printf("pid %d  gv %d\n",getpid(),globvar);

    if (rc > 0)
    {
        globvar += 2;
        printf("pid %d  gv %d\n",getpid(),globvar);
        wait(&status);
    }
    else
    {
        sleep(3);
        printf("pid %d  gv %d\n",getpid(),globvar);
    }
}
