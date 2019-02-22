#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv)
{
    int val, i, n, r;

    val = atoi(argv[1]);

    for (i=2, r=sqrt((double) val);  (val % i) != 0  &&  i < r;  i++)
        ;
    if ( (val % i) != 0)
       printf("%d is prime\n",val);
    else
       printf("%d is not prime\n",val);

    return 0;
}
