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

int sum_no_branch()
{
    /*todo 不使用分支进行求和，使用位运算
     t = (data[c] - 128) >> 31;
            sum += ~t & data[c];*/
    return sum;
}

int main()
{
    init();

/*todo
调用两个函数并计时，输出两种方案的执行时间。
*/
    printf("sum128 order exe_time %f ms, sum128: %d\n",exe_time,sum128());
}
