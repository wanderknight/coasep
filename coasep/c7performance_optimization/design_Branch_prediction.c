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

int sum_no_branch()
{
    /*todo ��ʹ�÷�֧������ͣ�ʹ��λ����
     t = (data[c] - 128) >> 31;
            sum += ~t & data[c];*/
    return sum;
}

int main()
{
    init();

/*todo
����������������ʱ��������ַ�����ִ��ʱ�䡣
*/
    printf("sum128 order exe_time %f ms, sum128: %d\n",exe_time,sum128());
}
