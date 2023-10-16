#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(short bits, short value)
{
    short i;
    for(i = bits-1; i >=0; i--)
    {
        if(value & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
}
short GetSign(short iNum)//获取符号位
{
    short iSign = iNum >> 15;
    if(iSign)//高位为1为负数
        return 1;
    else
        return 0;
}
short Ones_complement_Code(short iNum)//反码
{
    short iSign = GetSign(iNum);
    if(iSign)//为负数
    {
        iNum = ~iNum;
        iNum |= 1 << 15;
        return iNum;
    }
    else
    {
        return iNum;
    }
}
short  Complemental_Code(short iNum)//补码
{
    short iSign = GetSign(iNum);
    if(iSign)
    {
        printf("####");
        ShowValueBin(16,iNum);
        iNum = Ones_complement_Code(iNum)+1;
        printf("\n**************%d,%d\n",iSign,iNum);
        printf("####");
        ShowValueBin(16,iNum);
        printf("\n");
        return iNum;
    }
    else
    {
        return iNum;
    }
}

short Frame_Shift(short iNum)//移码
{
    short iSign = GetSign(iNum);
    if(iSign)
    {
        iNum &= ~(1 << 15);
        return iNum;
    }
    else
    {
        iNum |= 1 << 15;
        return iNum;
    }
}
short True_Code(short iNum)
{
    short iSign = GetSign(iNum);
    if(iSign)//负数在内存中是以补码的形式存在
    {
        iNum = Complemental_Code(iNum);
        return iNum;
    }
    else
    {
        return iNum;
    }
}
short main(short argc, char* argv[])
{
    /*****************************************************
    1. 正数：
    正数的原码、反码、补码都相同。
    2. 负数：
    原码：负数的绝对值，并且最高位为1。
    反码：原码的符号位不变，其他位按位取反。
    补码：在反码的基础上+1。
    3. 移码：
    无论是正/负数，都是在补码的基础上，符号位取反。
    ******************************************************/

    short True_Code1 = True_Code(1);
    short True_Code2 = True_Code(-1);

    short Complemental_Code1 = Complemental_Code(1);
    short Complemental_Code2 = Complemental_Code(-1);

    short Ones_complement1 = Ones_complement_Code(1);
    short Ones_complement2 = Ones_complement_Code(-1);

    short Frame_Shift1 = Frame_Shift(1);
    short Frame_Shift2 = Frame_Shift(-1);

    printf("True_Code1=%d\r\n", True_Code1);
    printf("True_Code2=%d\r\n", True_Code2);

    printf("Complemental_Code1=%d\r\n", Complemental_Code1);
    printf("Complemental_Code2=%d\r\n", Complemental_Code2);

    printf("Ones_complement1=%d\r\n", Ones_complement1);
    printf("Ones_complement2=%d\r\n", Ones_complement2);

    printf("Frame_Shift1=%d\r\n", Frame_Shift1);
    printf("Frame_Shift2=%d\r\n", Frame_Shift2);

    printf("\r\n");
    ShowValueBin(16, 1);
    printf("\r\n");
    ShowValueBin(16, -1);
    printf("\r\n");

    return 0;

}
