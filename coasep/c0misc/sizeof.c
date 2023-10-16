
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct student{
        int xuehao;
        char name[8];
    };

    printf("sizeof(char) = %d B\n",sizeof(char));
    printf("\n");

    printf("sizeof(short) = %d B\n",sizeof(short));
    printf(" \n");

    printf("sizeof(int) = %d B\n",sizeof(int));
    printf("sizeof(unsigned) = %d B\n",sizeof(unsigned));
    printf("sizeof(unsigned int) = %d B\n",sizeof(unsigned int));
    printf("sizeof(long) = %d B\n",sizeof(long));
    printf("sizeof(unsigned long) = %d B\n",sizeof(unsigned long));

    printf("sizeof(long long) = %d B\n",sizeof(long long));
    printf(" \n");

    printf("sizeof(float) = %d B\n",sizeof(float));
    printf("sizeof(double) = %d B\n",sizeof(double));
    printf("sizeof(long double) = %d B\n",sizeof(long double));
    printf(" \n");

    printf("sizeof(pointer *) = %d B\n",sizeof(int *));
    printf(" \n");


    printf("sizeof(struct) = %d B\n",sizeof(struct student));

    printf("sizeof(long int) = %d B\n",sizeof(long int));

    return 0;
}
