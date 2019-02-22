#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>


int main(int argc, char *argv[])
{
    int rc, status;
    void *region;
    int *psharedint;

 // region = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    region = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);
    if (region == ((void *) -1)) 
    {
        perror("mmap");
        return 1;
    }
    psharedint = (int *) region;
    printf("region %p  psharedint %p\n",region,psharedint);

    *psharedint = 0;

    rc = fork();
    printf("pid %d  *psharedint %d\n",getpid(),*psharedint);

    if (rc == 0)  // child
    {
        printf("pid %d  *psharedint %d ; spinning\n",getpid(),*psharedint);
        while ( ! *psharedint)
            ;
        printf("pid %d  *psharedint %d ; done\n",getpid(),*psharedint);
        exit(0);
    }

    printf("pid %d  *psharedint %d ; sleeping\n",getpid(),*psharedint);
    sleep(3);
    *psharedint = 1;  // release the child
    wait(&status);
    printf("pid %d  *psharedint %d ; done\n",getpid(),*psharedint);
}
