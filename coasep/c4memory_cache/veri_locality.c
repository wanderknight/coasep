#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "QPC_time_4locality.h"


int a[M][N];

void init()
{
    int i,j;
    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            a[i][j]=i+j*100;

}
/* 行优先计算 */
int sumarrayrows(int a[M][N])
{
    int i, j;
    float sum = 0;

    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            sum += a [i][j] ;
    //printf("sum is :%f  ",sum);
    return sum;
}

/* 列优先计算 */
int sumarraycols(int a[M][N])
{
    int i, j;
    float sum = 0;

    for (j = 0; j < N; j++)
        for (i = 0; i < M; i++)
            sum += a [i][j];
    //printf("sum is :%f  ",sum);
   return sum;
}

int main()
{
    double exe_time;
    init();

    exe_time = qpc_time(sumarrayrows,a);
    printf("sumarrayrows exe_time:%f ms\n",exe_time);

    exe_time = qpc_time(sumarraycols,a);
    printf("sumarraycols exe_time:%f ms\n",exe_time);

    return 0;
}
