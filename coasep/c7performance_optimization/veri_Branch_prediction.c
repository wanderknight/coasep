#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ArraySize (1 << 20) //1M������

int data[ArraySize];

void init()
{
    int i;
    for(i=0; i<ArraySize; i++)
    {
        data[i] = rand() % 256;
    }

}

/* �Դ���128���������� */
int sum128()
{
    int i,sum=0;
    for(i=0; i<ArraySize; i++)
    {
        if(data[i]>=128) sum = sum + data[i] ;
    }
    return sum;
}


void Quicksort(int a[], int left, int right) {   //���ź��� ���ú�����Quicksort(arr, 0, n - 1);
	int temp;
	int mid = a[(left + right) / 2];            //�һ�׼ֵ
	int i = left;
	int j = right;
    //�������һ�����ڻ�׼ֵ���������Ҳ���һ��С�ڻ�׼��������Ȼ�󽻻�λ��
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
	if (i < right) Quicksort(a, i, right); //�ݹ�
	if (j > left) Quicksort(a, left, j);   //�ݹ�
}


int main()
{
    init();

    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    //��ѯcpu��Ƶ
    QueryPerformanceFrequency(&freq);

     //����ʱ���ӳ�
    QueryPerformanceCounter(&start);
    sum128();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum128 exe_time %f ms, sum128: %d\n",exe_time,sum128());

    Quicksort(data,0,ArraySize-1);

    //����ʱ���ӳ�
    QueryPerformanceCounter(&start);
    sum128();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum128 order exe_time %f ms, sum128: %d\n",exe_time,sum128());
}
