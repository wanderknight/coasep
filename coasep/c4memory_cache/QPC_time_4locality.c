/*���㾫ȷʱ�䣬*/

#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "QPC_time_4locality.h"

double qpc_time(test_funct f, int param1[][N])
 {
    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    //��ѯcpu��Ƶ
    QueryPerformanceFrequency(&freq);

    //����ʱ���ӳ�
    QueryPerformanceCounter(&start);

    f(param1);
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    return exe_time;
}
