#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    int rc;

    if ((rc = fork()) == -1)
    {
       printf("fork failed\n");
       exit(-1);
    }
    else if (rc == 0)
    {
       printf("I am child; pid=%d  rc = %d\n",getpid(),rc);
       // exit(0);
    }
    else
       printf("I am parent; rc = %d\n",rc);
    printf("%d got rc=%d\n", getpid(), rc);
}
