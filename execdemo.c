#include <stdio.h>
#include <unistd.h>

void main()
{
    char *args[] = { "/bin/date", NULL };

    printf("should see this message\n");
    execve("/bin/date",args,NULL);
    printf("should NOT see this message\n");
}
