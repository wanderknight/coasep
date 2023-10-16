#include <stdio.h>

main()
{
    short a, b;
    a=32767;
    b=a+2;
    printf("length of short: %d \n bit", sizeof(short)*8);
    printf("%d,%d\n", a+2, b);

    return 0;

}

