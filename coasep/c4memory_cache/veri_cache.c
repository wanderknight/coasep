#include<stdio.h>
#include<stdlib.h>


/*参数信息
num:cache level
    0：L1D
    1：L1I
    2：L2
    3：L3
*/
void cpuidTest(int num)
{
    int  val_eax, val_ebx, val_ecx, val_edx;
    asm("cpuid"
                : "=a" (val_eax),
        "=b" (val_ebx),
        "=c" (val_ecx),
        "=d" (val_edx)
                : "a" (4), "c"(num));

    int ways,partitions,line_Size, sets;

    ways = val_ebx >> 22;
    partitions = (val_ebx >> 12) & 0x3FF;
    line_Size = (val_ebx) & 0xFFF;
    sets = val_ecx;
    printf("\n\n%d level cache:\n",num);

    printf("Cache L%d size: %d KB\n",num,
           (ways + 1)*(partitions + 1)*(line_Size + 1)*(sets + 1)/1024);

    //printf("eax: 0x%08X\n", val_eax);
    //printf("ebx: 0x%08X\n", val_ebx);
    //printf("ecx: 0x%08X\n", val_ecx);
    //printf("edx: 0x%08X\n", val_edx);

    //printf("ways: %d\n", ways+1);
    //printf("partitions: %d\n", partitions+1);
    //printf("line_size: %d\n", line_Size+1);
    //printf("sets: %d\n", sets+1);
}


int main()
{
    cpuidTest(0);
    cpuidTest(1);
    cpuidTest(2);
    cpuidTest(3);
    return 0;
}
