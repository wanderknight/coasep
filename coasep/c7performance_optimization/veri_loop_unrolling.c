#include <stdio.h>
#include <windows.h>

#define M 100000000
#define TIMES 1 //如果执行时间太短，无法观察到实验现象，可以放大此数值
int a[M];

void init()
{
    int i;
    for (i = 0; i < M; i++)
        a[i]=i+1;

}

long loop_unrolling4()
{
    long sum=0,sum0=0,sum1=0,sum2=0,sum3=0;
    int i,limit;
    int times;
    for(times=0; times<TIMES; times++)
    {
        limit = M -4;
        for (i = 0; i < limit; i=i+4)
        {
            sum0 = sum0 + a[i];
            sum1 = sum1 + a[i+1];
            sum2 = sum2 + a[i+2];
            sum3 = sum3 + a[i+3];
        }
        for(; i<M; i++)
            sum0 = sum0+ a[i];
        sum=sum0+sum1+sum2+sum3;
    }
    return sum;
}


long loop()
{
    long sum;
    int i,times;
    for(times=0; times<TIMES; times++)
    {
        sum=0;
        for(i=0; i<M; i++)
            sum = sum+ a[i];
    }
    return sum;
}

int main()
{
    int sum;
    init();

    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    //查询cpu主频
    QueryPerformanceFrequency(&freq);


    QueryPerformanceCounter(&start);
    sum = loop();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("loop            exetime : %f  result:%d\n",exe_time,sum);


    //计算时间延迟
    QueryPerformanceCounter(&start);
    sum = loop_unrolling4();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("loop_unrolling4 exetime :%f  result:%d\n",exe_time,sum);


}


