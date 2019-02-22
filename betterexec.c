#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    int i, rc, s;
    char *args[] = { "/bin/date", NULL };

    printf("pid=%d\n",getpid());
    rc = fork();
    if (rc == 0)  /* child */
    {
	printf("child pid=%d\n",getpid());
	execve("/bin/date",args,NULL);
	printf("should NOT see this message\n");
    }
    printf("rc=%d\n",rc);
    i = wait(&s);
    printf("i=%d\n",i);
}
