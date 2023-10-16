#include <stdio.h>

#define P 100
int a[P][P][P];

int sumarray3d(int a[P][P][P])
{
    int i, j, k, sum = 0;
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < P; j++)
        {
            for (k = 0; k < P; k++)
            {
                sum += a[k][i][j] ;
            }
        }
    }
    return sum;
}

void init()
{
    int i,j,k;
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < P; j++)
        {
            for (k = 0; k < P; k++)
            {
                a[k][i][j]= i+j+k ;
            }
        }
    }
}

int main()
{
    init();
    printf("%d\n",sumarray3d(a));
    return 0;
}
