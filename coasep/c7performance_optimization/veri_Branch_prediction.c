#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ArraySize (1 << 20) //1M个数据

int data[ArraySize];

void init()
{
    int i;
    for(i=0; i<ArraySize; i++)
    {
        data[i] = rand() % 256;
    }

}

/* 对大于128的项进行求和 */
int sum128()
{
    int i,sum=0;
    for(i=0; i<ArraySize; i++)
    {
        if(data[i]>=128) sum = sum + data[i] ;
    }
    return sum;
}


void Quicksort(int a[], int left, int right) {   //快排函数 调用函数：Quicksort(arr, 0, n - 1);
	int temp;
	int mid = a[(left + right) / 2];            //找基准值
	int i = left;
	int j = right;
    //在左侧找一个大于基准值的数，在右侧找一个小于基准数的数，然后交换位置
	while (i <= j) {
		while (a[i] < mid) i++;
		while (a[j] > mid) j--;
		if (i <= j) {
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	if (i < right) Quicksort(a, i, right); //递归
	if (j > left) Quicksort(a, left, j);   //递归
}


int main()
{
    init();

    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    //查询cpu主频
    QueryPerformanceFrequency(&freq);

     //计算时间延迟
    QueryPerformanceCounter(&start);
    sum128();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum128 exe_time %f ms, sum128: %d\n",exe_time,sum128());

    Quicksort(data,0,ArraySize-1);

    //计算时间延迟
    QueryPerformanceCounter(&start);
    sum128();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum128 order exe_time %f ms, sum128: %d\n",exe_time,sum128());
}
