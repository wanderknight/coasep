/*计算精确时间，查询cpu主频*/

#include <time.h>
#include <windows.h>
#include <stdio.h>

void func_use_time_s()
{
    Sleep(2000); //单位：ms

}

void func_use_time_ms()
{
    Sleep(100); //单位：ms

}

void func_use_time_ns()
{
    int a[1000],i;
    for(i=0; i<100; i++)
        a[i] = a[i]+1;
}

void func_use_time()
{
    func_use_time_ns();
}


/*difftime返回的精度为s*/
double time_time()
{
    double exe_time;
    time_t start,end;
    start = time(NULL);

    func_use_time();
    end =time(NULL);
    exe_time = difftime(end,start)*1000;
    return exe_time;
}

/*clock返回的精度为 ms*/
double time_clock()
{
    float exe_time;
    clock_t start,end;
    start = clock();

    func_use_time();
    end = clock();
    exe_time = (double)(end - start);
    return exe_time;
}

/*QueryPerformanceCounter 返回的精度为频率数*/
double time_QPC()
{
    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    //查询cpu主频
    QueryPerformanceFrequency(&freq);
    double frequence = freq.QuadPart*1024.0/1000/1000/1000;
    //fprintf(stdout, "The frequency of your pc is %fGHz.\n", frequence);


    //计算时间延迟
    QueryPerformanceCounter(&start);

    func_use_time();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;

    //fprintf(stdout, "Your program executed time is %20.12fms.\n", exe_time);
    return exe_time;
}

int main(int argc, char **argv)
{
    printf("time.h 的time  函数 =%20.15fms\n",time_time());
    printf("time.h 的clock 函数 =%20.15fms\n",time_clock());
    printf("time.h 的clock 函数 =%20.15fms\n",time_QPC());
    printf("%lf\n",(double)1);
    return 0;
}
